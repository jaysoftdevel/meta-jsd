/*
 *
 * StepperMotor_Control.c
 *
 * Possible items:
 * H-Bridge: sn754410
 * step motor: TMCM-MOTOR
 *
 * according to guide:
 * http://www.instructables.com/id/Drive-a-Stepper-Motor-with-an-AVR-Microprocessor/?ALLSTEPS
 *
 */

#ifndef STEPPERMOTOR_CONTROL_L_C
#define STEPPERMOTOR_CONTROL_L_C

/* Kernel Programming */
#define MODULE
#define LINUX
#define __KERNEL__

//#define DEBUG

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put_user */
#include <asm/errno.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#include "stepperL.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JaySoftDevel");
MODULE_DESCRIPTION("Linux Kernel Module to drive SN754410 Quadruple Half-H Driver via GPIO");
MODULE_VERSION("0.4");

// Keep this order!!
static struct tPos coilPins = {COIL_PIN_NORTH, COIL_PIN_SOUTH, COIL_PIN_EAST, COIL_PIN_WEST};

static dev_t second;	  // Global variable for the second device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl;  // Global variable for the device class

// used for buffer
char *rx_buffer;
int BUFFER_SIZE = 8;

static struct file_operations pugs_fops = {
	.owner = THIS_MODULE,
	.open = stepperL_open,
	.unlocked_ioctl = stepperL_control,
	.write = stepperL_write,
	.release = stepperL_close,
};

// Struct for each GPIO pin
struct gpio_pin
{
	const char *name;
	unsigned gpio;
};

// Struct to point to all GPIO pins
struct gpio_platform_data
{
	struct gpio_pin *pins;
	int num_pins;
};

// Struct for interface definition
static struct gpio_pin stepperL_gpio_pins[] = {
	{
		.name = "stepperL::north",
		.gpio =
			COIL_PIN_NORTH,
	},
	{
		.name = "stepperL::east",
		.gpio = COIL_PIN_EAST,
	},
	{
		.name =
			"stepperL::south",
		.gpio = COIL_PIN_SOUTH,
	},
	{
		.name = "stepperL::west",
		.gpio =
			COIL_PIN_WEST,
	},
};

static struct gpio_platform_data stepperL_gpio_pin_info = {
	.pins =
		stepperL_gpio_pins,
	.num_pins = ARRAY_SIZE(stepperL_gpio_pins),
};

/**
 * @brief
 *
 * This stepper function is based on double phase steps which
 * makes the QSH4218 motor run way faster and wayyyy smoother.
 *
 * @return ** int -> no specific reason yet.
 *
 * * 2DO: make fct void to remove stack and runtime overhead for push and pop during context change!!
 *
 */
int stepFwdL(void)
{
	uint8 i;
	for (i = 0; i < NUM_OF_COILS; i++)
	{
		if (i == coilPins.pos || i == ((unsigned)(coilPins.pos + 1) & 0x03)) // cast to bit field to catch overrun!
		{
#ifdef DEBUG
			printk("[%s] set pin %i high\n", __FUNCTION__, coilPins.coils[i]);
#endif
			gpio_set_value(coilPins.coils[i], 1);
		}
		else
		{
#ifdef DEBUG
			printk("[%s] set pin %i low\n", __FUNCTION__, coilPins.coils[i]);
#endif
			gpio_set_value(coilPins.coils[i], 0);
		}
	}
	coilPins.pos++;
	return (0);
}

int stepRevL(void)
{
	uint8 i;
	for (i = 0; i < NUM_OF_COILS; i++)
	{
		if (i == coilPins.pos || i == ((unsigned)(coilPins.pos + 1) & 0x03)) // cast to bit field to catch overrun!
		{
#ifdef DEBUG
			printk("[%s] set pin %i high\n", __FUNCTION__, coilPins.coils[i]);
#endif
			gpio_set_value(coilPins.coils[i], 1);
		}
		else
		{
#ifdef DEBUG
			printk("[%s] set pin %i low\n", __FUNCTION__, coilPins.coils[i]);
#endif
			gpio_set_value(coilPins.coils[i], 0);
		}
	}
	coilPins.pos--;
	return (0);
}

int stepLNone(void)
{
#ifdef DEBUG
	printk("set all pins to low\n");
#endif
	gpio_set_value(COIL_PIN_NORTH, 0);
	gpio_set_value(COIL_PIN_EAST, 0);
	gpio_set_value(COIL_PIN_SOUTH, 0);
	gpio_set_value(COIL_PIN_WEST, 0);
	return (0);
}

static int __init stepperL_init(void)
{
	int err, i;
	i = 0;
#ifdef DEBUG
	printk("[%s] initializiing stepperL\n", __FUNCTION__);
#endif
	// allocate a buffer and zero it out
	rx_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	memset(rx_buffer, 0, BUFFER_SIZE);
#ifdef DEBUG
	printk("[%s] registering stepperL chr dev\n", __FUNCTION__);
#endif // DEBUG
	// register a character device
	if (alloc_chrdev_region(&second, 0, 1, "stepperL") < 0)
	{
		return -1;
	}
	if ((cl = class_create(THIS_MODULE, "chardrv2")) == NULL)
	{
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] creating stepperL device\n", __FUNCTION__);
#endif // DEBUG
	if (device_create(cl, NULL, second, NULL, "stepperL") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] stepperL cdev init\n", __FUNCTION__);
#endif // DEBUG
	cdev_init(&c_dev, &pugs_fops);
	if (cdev_add(&c_dev, second, 1) == -1)
	{
		device_destroy(cl, second);
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] registering stepperL gpio pins\n", __FUNCTION__);
#endif
	// request access to GPIO, set them all as outputs (initially low)
	for (i = 0; i < stepperL_gpio_pin_info.num_pins; i++)
	{
#ifdef DEBUG
		printk("[%s] register pin %d with gpio %d with name %s\n", __FUNCTION__, i, stepperL_gpio_pins[i].gpio, stepperL_gpio_pins[i].name);
#endif
		err = gpio_request(stepperL_gpio_pins[i].gpio, stepperL_gpio_pins[i].name);
		if (err)
		{
#ifdef DEBUG
			printk("[%s] Could not get access to GPIO %i, error code: %i\n", __FUNCTION__, stepperL_gpio_pins[i].gpio, err);
#endif
			return -1;
		}
		err = gpio_direction_output(stepperL_gpio_pins[i].gpio, 0);
		if (err)
		{
#ifdef DEBUG
			printk("[%s] Could not set value of GPIO %i, error code: %i\n", __FUNCTION__, stepperL_gpio_pins[i].gpio, err);
#endif
			return -1;
		}
	}
// ready to go!
#ifdef DEBUG
	printk("[%s] stepperL registered!\n", __FUNCTION__);
#endif
	return 0;
}

static int stepperL_open(struct inode *i, struct file *f)
{
#ifdef DEBUG
	printk("[%s] opening stepperL\n", __FUNCTION__);
#endif
	return 0;
}

long stepperL_control(struct file *f, unsigned int control, unsigned long value)
{
	int i;
#ifdef DEBUG
	printk("[%s] control: %x value: %x\n", __FUNCTION__, control, value);
#endif
	if (control == IOCTL_STEPPER_L_STEP_FWD)
	{
#ifdef DEBUG
		printk("[%s] Received stepperL forward step\n", __FUNCTION__);
#endif
		stepFwdL();
	}
	else if (control == IOCTL_STEPPER_L_STEP_REV)
	{
#ifdef DEBUG
		printk("[%s] Received stepperL reverse step\n", __FUNCTION__);
#endif

		stepRevL();
	}
	else if (control == IOCTL_STEPPER_L_STEP_NONE)
	{
#ifdef DEBUG
		printk("[%s] Received stepperL stop step\n", __FUNCTION__);
#endif
		stepLNone();
	}
	else
	{
#ifdef DEBUG
		printk("[%s] Received unknown stepperL command: %i\n", __FUNCTION__, control);
#endif
		return -1;
	}
	return 0;
}

static ssize_t stepperL_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
#ifdef DEBUG
	printk("[%s] write len: %x\n", __FUNCTION__, len);
#endif
	// zero the input buffer
	memset(rx_buffer, 0, BUFFER_SIZE);

	// copy the incoming data from userspace to a buffer in kernel space
	int retval = raw_copy_from_user(rx_buffer, buf, len);
#ifdef DEBUG
	printk("[%s] Received data: %s length: %x\n", __FUNCTION__, rx_buffer, len);
#endif
	return len;
}

static int stepperL_close(struct inode *i, struct file *f)
{
#ifdef DEBUG
	printk("[%s] closing stepperL\n", __FUNCTION__);
#endif
	return 0;
}

static void __exit stepperL_exit(void)
{
#ifdef DEBUG
	printk("[%s] shutting down...", __FUNCTION__);
#endif
	// release buffer
	if (rx_buffer)
	{
		kfree(rx_buffer);
	}

	// release GPIO
	int i = 0;
	for (i = 0; i < stepperL_gpio_pin_info.num_pins; i++)
	{
		gpio_free(stepperL_gpio_pins[i].gpio);
	}

	// unregister character device
	cdev_del(&c_dev);
	device_destroy(cl, second);
	class_destroy(cl);
	unregister_chrdev_region(second, 1);
#ifdef DEBUG
	printk("[%s] stepperL unregistered\n", __FUNCTION__);
#endif
}

/********************/

int init_module(void)
{
	int i, j;
#ifdef DEBUG
	printk("Hello World stepperL!\n");
#endif
	stepperL_init();
	stepFwdL();
	msleep(50);
	stepRevL();
	// printk("Prepare for max speed test\n");
	// msleep(2000);
	// 	printk("cycle time STEPPER_L_INTERVAL %i us\n",STEPPER_L_INTERVAL);
	// 	msleep(2000);
	// 	for (i = 0; j < 10000; j++)
	// 	{
	// 		udelay(STEPPER_L_INTERVAL);
	// 		stepFwdL();
	// 	}
	stepLNone();
	return 0;
}

void cleanup_module(void)
{
	stepperL_exit();
#ifdef DEBUG
	printk("Goodbye Cruel World stepperL!\n");
#endif
}

MODULE_LICENSE("GPL");

#endif /* STEPPERMOTOR_CONTROL_L_H */
