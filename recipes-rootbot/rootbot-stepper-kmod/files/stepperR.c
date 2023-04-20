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

#ifndef STEPPERMOTOR_CONTROL_R_C
#define STEPPERMOTOR_CONTROL_R_C

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
#include <asm/delay.h>

#include "stepperR.h"

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
	.open = stepperR_open,
	.unlocked_ioctl = stepperR_control,
	.write = stepperR_write,
	.release = stepperR_close,
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
static struct gpio_pin stepperR_gpio_pins[] = {
	{
		.name = "stepperR::north",
		.gpio =
			COIL_PIN_NORTH,
	},
	{
		.name = "stepperR::east",
		.gpio = COIL_PIN_EAST,
	},
	{
		.name =
			"stepperR::south",
		.gpio = COIL_PIN_SOUTH,
	},
	{
		.name = "stepperR::west",
		.gpio =
			COIL_PIN_WEST,
	},
};

static struct gpio_platform_data stepperR_gpio_pin_info = {
	.pins =
		stepperR_gpio_pins,
	.num_pins = ARRAY_SIZE(stepperR_gpio_pins),
};

/**
 * @brief
 *
 * This stepper function is based on double phase steps which
 * makes the QSH4218 motor run way faster and wayyyy smoother.
 *
 * @return ** int -> no specific reason yet...
 *
 * * 2DO: make fct void to remove stack and runtime overhead for push and pop during context change!!
 *
 */
int stepFwdR(void)
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

int stepRevR(void)
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

int stepRNone(void)
{
#ifdef DEBUG
	printk("[%s] set all pins to low\n", __FUNCTION__);
#endif
	gpio_set_value(COIL_PIN_NORTH, 0);
	gpio_set_value(COIL_PIN_EAST, 0);
	gpio_set_value(COIL_PIN_SOUTH, 0);
	gpio_set_value(COIL_PIN_WEST, 0);
	return (0);
}

static int __init stepperR_init(void)
{
#ifdef DEBUG
	printk("[%s] initializiing stepperR\n", __FUNCTION__);
#endif
	// allocate a buffer and zero it out
	rx_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	memset(rx_buffer, 0, BUFFER_SIZE);
#ifdef DEBUG
	printk("[%s] registering stepperR chr dev\n", __FUNCTION__);
#endif // DEBUG
	// register a character device
	if (alloc_chrdev_region(&second, 0, 1, "stepperR") < 0)
	{
		return -1;
	}
	if ((cl = class_create(THIS_MODULE, "chardrv3")) == NULL)
	{
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] creating stepperR device\n", __FUNCTION__);
#endif // DEBUG
	if (device_create(cl, NULL, second, NULL, "stepperR") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] stepperR cdev init\n", __FUNCTION__);
#endif // DEBUG
	cdev_init(&c_dev, &pugs_fops);
	if (cdev_add(&c_dev, second, 1) == -1)
	{
		device_destroy(cl, second);
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}

	// request access to GPIO, set them all as outputs (initially low)
#ifdef DEBUG
	printk("[%s] registering stepperR gpio pins\n", __FUNCTION__);
#endif
	int err, i;
	i = 0;
	for (i = 0; i < stepperR_gpio_pin_info.num_pins; i++)
	{
#ifdef DEBUG
		printk("[%s] register pin %d with gpio %d with name %s\n", __FUNCTION__, i, stepperR_gpio_pins[i].gpio, stepperR_gpio_pins[i].name);
#endif
		err = gpio_request(stepperR_gpio_pins[i].gpio, stepperR_gpio_pins[i].name);
		if (err)
		{
#ifdef DEBUG
			printk("[%s] Could not get access to GPIO %i, error code: %i\n", __FUNCTION__, stepperR_gpio_pins[i].gpio, err);
#endif
			return -1;
		}
		err = gpio_direction_output(stepperR_gpio_pins[i].gpio, 0);
		if (err)
		{
#ifdef DEBUG
			printk("[%s] Could not set value of GPIO %i, error code: %i\n", __FUNCTION__, stepperR_gpio_pins[i].gpio, err);
#endif
			return -1;
		}
	}
// ready to go!
#ifdef DEBUG
	printk("[%s] stepperR registered!\n", __FUNCTION__);
#endif
	return 0;
}

static int stepperR_open(struct inode *i, struct file *f)
{
#ifdef DEBUG
	printk("[%s] opening stepperR\n", __FUNCTION__);
#endif
	return 0;
}

long stepperR_control(struct file *f, unsigned int control, unsigned long value)
{
	int i;
#ifdef DEBUG
	printk("[%s] control: %x value: %x\n", __FUNCTION__, control, value);
#endif
	if (control == IOCTL_STEPPER_R_STEP_FWD)
	{
#ifdef DEBUG
		printk("[%s] Received stepperR forward step\n", __FUNCTION__);
#endif
		stepFwdR();
	}
	else if (control == IOCTL_STEPPER_R_STEP_REV)
	{
#ifdef DEBUG
		printk("[%s] Received stepperR reverse step\n", __FUNCTION__);
#endif

		stepRevR();
	}
	else if (control == IOCTL_STEPPER_R_STEP_NONE)
	{
#ifdef DEBUG
		printk("[%s] Received stepperR stop step\n", __FUNCTION__);
#endif
		stepRNone();
	}
	else
	{
#ifdef DEBUG
		printk("[%s] Received unknown stepperR command: %i\n", __FUNCTION__, control);
#endif
		return -1;
	}
	return 0;
}

static ssize_t stepperR_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
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

static int stepperR_close(struct inode *i, struct file *f)
{
#ifdef DEBUG
	printk("[%s] closing stepperR\n", __FUNCTION__);
#endif
	return 0;
}

static void __exit stepperR_exit(void)
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
	for (i = 0; i < stepperR_gpio_pin_info.num_pins; i++)
	{
		gpio_free(stepperR_gpio_pins[i].gpio);
	}

	// unregister character device
	cdev_del(&c_dev);
	device_destroy(cl, second);
	class_destroy(cl);
	unregister_chrdev_region(second, 1);
#ifdef DEBUG
	printk("[%s] stepperR unregistered\n", __FUNCTION__);
#endif
}

/********************/

int init_module(void)
{
	int i, j;
#ifdef DEBUG
	printk("Hello World stepperR!\n");
#endif
	stepperR_init();
	stepFwdR();
	msleep(50);
	stepRevR();
	// printk("Prepare for max speed test\n");
	// printk("cycle time STEPPER_R_INTERVAL %i us\n", STEPPER_R_INTERVAL);
	// msleep(2000);
	// for (i = 0;i<10000;i++)
	// {
	// 	udelay(STEPPER_R_INTERVAL);
	// 	stepFwdR();
	// }
	stepRNone();
	return 0;
}

void cleanup_module(void)
{
	stepperR_exit();
#ifdef DEBUG
	printk("Goodbye Cruel World stepperR!\n");
#endif
}

MODULE_LICENSE("GPL");

#endif /* STEPPERMOTOR_CONTROL_R_H */
