#ifndef HCSR04_GPIO_C
#define HCSR04_GPIO_C

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
#include <linux/interrupt.h>
#include <linux/ktime.h>

#include "hcsr04-gpio.h"

static dev_t second;	  // Global variable for the second device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl;  // Global variable for the device class

static ktime_t start, end; // track sonar echo
static int duration;	   // used for time measurements

// used for buffer
char *rx_buffer;

static struct file_operations pugs_fops = {.owner = THIS_MODULE,
										   .open = hcsr04_open,
										   .release = hcsr04_close,
										   .unlocked_ioctl = hcsr04_control,
										   .write = hcsr04_write,
										   .read = hcsr04_read};

// Struct for each GPIO pin
struct gpio_pin
{
	const char *name;
	unsigned gpio;
	unsigned irq;
};

// Struct to point to all GPIO pins
struct gpio_platform_data
{
	struct gpio_pin *pins;
	int num_pins;
};

// Struct for interface definition
static struct gpio_pin hcsr04_gpio_pins[] =
	{
		{
			.name = "hcsr04-trigger_FL",
			.gpio = TRIGGER_FL,
		},
		{
			.name = "hcsr04-echo_FL",
			.gpio = ECHO_FL,
		},
		{
			.name = "hcsr04-trigger_FC",
			.gpio = TRIGGER_FC,
		},
		{
			.name = "hcsr04-echo_FC",
			.gpio = ECHO_FC,
		},
		{
			.name = "hcsr04-trigger_FR",
			.gpio = TRIGGER_FR,
		},
		{
			.name = "hcsr04-echo_FR",
			.gpio = ECHO_FR,
		},
		{
			.name = "hcsr04-trigger_RR",
			.gpio = TRIGGER_RR,
		},
		{
			.name = "hcsr04-echo_RR",
			.gpio = ECHO_RR,
		},
		{
			.name = "hcsr04-trigger_RL",
			.gpio = TRIGGER_RL,
		},
		{
			.name = "hcsr04-echo_RL",
			.gpio = ECHO_RL,
		},
};

static struct gpio_platform_data hcsr04_gpio_pin_info = {
	.pins =
		hcsr04_gpio_pins,
	.num_pins = ARRAY_SIZE(hcsr04_gpio_pins),
};

// used for buffer
char *rx_buffer;
int BUFFER_SIZE = 5 * 4; // 4 bytes for each HCSR04 sensor

long echoToDistance(long duration)
{
	return (long)(duration / 5844);
}

// static irqreturn_t MeasureISR(int irq, void *dev)
// {
// 	// Not sure why rising edge and falling edge timestamps cannot be compared
// 	// in two separate ISR calls. Just bullshit is returned!!!
// 	// if(start==0){
// 	// 	start=ktime_get();
// 	// 	printk("[%s] start measuring, %li\n",__FUNCTION__, tstart.tv_nsec);
// 	// }
// 	// else{
// 	// 	end=ktime_get_ts64();
// 	// 	printk("[%s] stop measuring, distance: %ld!!!\n",__FUNCTION__,echoToDistance((int)(tend.tv_nsec - tstart.tv_nsec)));
// 	// 	start=0; //reset measurement
// 	// }

// 	start = ktime_get_ns();
// 	while (gpio_get_value(hcsr04_gpio_pins[1].gpio) != 0)
// 	{
// 		// ToDo: define exit strategy
// 	}
// 	end = ktime_get_ns();
// #ifdef DEBUG
// 	printk("[%s] IRQ finished, duration: %li distance: %limm\n", __FUNCTION__, (long)(end - start), echoToDistance((long)(end - start)));
// #endif
// 	return IRQ_HANDLED;
// }

// trigger FL
long getDistanceFL(void)
{
#ifdef DEBUG
	printk("waiting for %s pin\n", hcsr04_gpio_pins[1].name);
#endif
	gpio_set_value(hcsr04_gpio_pins[0].gpio, 1);
	msleep(2);
	gpio_set_value(hcsr04_gpio_pins[0].gpio, 0);
	while (gpio_get_value(hcsr04_gpio_pins[1].gpio) != 1)
	{
		// define exit strategy
	}
	start = ktime_get_ns();
	while (gpio_get_value(hcsr04_gpio_pins[1].gpio) != 0)
	{
		// define exit strategy
	}
	end = ktime_get_ns();
	duration = (int)end - start;
	// !!! use copy to user mechanism!
#ifdef DEBUG
	printk("### FL: %u mm#\n", echoToDistance(duration));
#endif
	return echoToDistance(duration);
}

// trigger FC
long getDistanceFC(void)
{
	// gpio_set_value(hcsr04_gpio_pins[2].gpio, 0);
	// gpio_set_value(hcsr04_gpio_pins[3].gpio, 0);
	// msleep(10);
#ifdef DEBUG
	printk("waiting for %s pin\n", hcsr04_gpio_pins[3].name);
#endif
	gpio_set_value(hcsr04_gpio_pins[2].gpio, 1);
	msleep(2);
	gpio_set_value(hcsr04_gpio_pins[2].gpio, 0);
	while (gpio_get_value(hcsr04_gpio_pins[3].gpio) != 1)
	{
		// define exit strategy
	}
	start = ktime_get_ns();
	while (gpio_get_value(hcsr04_gpio_pins[3].gpio) != 0)
	{
		// define exit strategy
	}
	end = ktime_get_ns();
	duration = (int)end - start;
	// !!! use copy to user mechanism!
#ifdef DEBUG
	printk("### FC: %u mm#\n", echoToDistance(duration));
#endif
	return echoToDistance(duration);
}

// trigger FR
long getDistanceFR(void)
{
	// gpio_set_value(hcsr04_gpio_pins[4].gpio, 0);
	// gpio_set_value(hcsr04_gpio_pins[5].gpio, 0);
	// msleep(10);
#ifdef DEBUG
	printk("waiting for %s pin\n", hcsr04_gpio_pins[5].name);
#endif
	gpio_set_value(hcsr04_gpio_pins[4].gpio, 1);
	msleep(2);
	gpio_set_value(hcsr04_gpio_pins[4].gpio, 0);
	while (gpio_get_value(hcsr04_gpio_pins[5].gpio) != 1)
	{
		// define exit strategy
	}
	start = ktime_get_ns();
	while (gpio_get_value(hcsr04_gpio_pins[5].gpio) != 0)
	{
		// define exit strategy
	}
	end = ktime_get_ns();
	duration = (int)end - start;
	// !!! use copy to user mechanism!
#ifdef DEBUG
	printk("### FR: %u mm#\n", echoToDistance(duration));
#endif
	return echoToDistance(duration);
}

// trigger RL
long getDistanceRL(void)
{
	// gpio_set_value(hcsr04_gpio_pins[6].gpio, 0);
	// gpio_set_value(hcsr04_gpio_pins[7].gpio, 0);
	// msleep(10);
#ifdef DEBUG
	printk("waiting for %s pin\n", hcsr04_gpio_pins[7].name);
#endif
	gpio_set_value(hcsr04_gpio_pins[6].gpio, 1);
	msleep(2);
	gpio_set_value(hcsr04_gpio_pins[6].gpio, 0);
	while (gpio_get_value(hcsr04_gpio_pins[7].gpio) != 1)
	{
		// define exit strategy
	}
	start = ktime_get_ns();
	while (gpio_get_value(hcsr04_gpio_pins[7].gpio) != 0)
	{
		// define exit strategy
	}
	end = ktime_get_ns();
	duration = (int)end - start;
	// !!! use copy to user mechanism!
#ifdef DEBUG
	printk("### RL: %u mm#\n", echoToDistance(duration));
#endif
	return echoToDistance(duration);
}

// trigger RR
long getDistanceRR(void)
{
	// gpio_set_value(hcsr04_gpio_pins[8].gpio, 0);
	// gpio_set_value(hcsr04_gpio_pins[9].gpio, 0);
	// msleep(10);
#ifdef DEBUG
	printk("waiting for %s pin\n", hcsr04_gpio_pins[9].name);
#endif
	gpio_set_value(hcsr04_gpio_pins[8].gpio, 1);
	msleep(2);
	gpio_set_value(hcsr04_gpio_pins[8].gpio, 0);
	while (gpio_get_value(hcsr04_gpio_pins[9].gpio) != 1)
	{
		// define exit strategy
	}
	start = ktime_get_ns();
	while (gpio_get_value(hcsr04_gpio_pins[9].gpio) != 0)
	{
		// define exit strategy
	}
	end = ktime_get_ns();
	duration = (int)end - start;
	// !!! use copy to user mechanism!
#ifdef DEBUG
	printk("### RR: %u mm#\n", echoToDistance(duration));
#endif
	return echoToDistance(duration);
}

// init GPIOs
static int __init hcsr04_init(void)
{
	int err, i, irq;
#ifdef DEBUG
	printk("[%s] initializiing GPIOs\n", __FUNCTION__);
#endif
	// allocate a buffer and zero it out
	rx_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	memset(rx_buffer, 0, BUFFER_SIZE);
#ifdef DEBUG
	printk("[%s] registering HCSR04-GPIO chr dev\n", __FUNCTION__);
#endif // DEBUG
	// register a character device
	if (alloc_chrdev_region(&second, 0, 1, "hcsr04") < 0)
	{
#ifdef DEBUG
		printk("[%s] registering HCSR04-GPIO chr dev failed!!!\n", __FUNCTION__);
#endif // DEBUG
		return -1;
	}
	// create sysfs class
	if ((cl = class_create(THIS_MODULE, "chardrv-gpio")) == NULL)
	{
#ifdef DEBUG
		printk("[%s] registering HCSR04-GPIO sysfs class failed!!!\n", __FUNCTION__);
#endif // DEBUG
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] creating HCSR04-GPIO device\n", __FUNCTION__);
#endif // DEBUG
	if (device_create(cl, NULL, second, NULL, "hcsr04") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] HCSR04_GPIO cdev init\n", __FUNCTION__);
#endif // DEBUG
	cdev_init(&c_dev, &pugs_fops);
	if (cdev_add(&c_dev, second, 1) == -1)
	{
		device_destroy(cl, second);
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}

// request access to GPIO
#ifdef DEBUG
	printk("[%s] registering HCSR04_GPIO pins\n", __FUNCTION__);
#endif
	for (i = 0; i < hcsr04_gpio_pin_info.num_pins; i++)
	{
#ifdef DEBUG
		printk("[%s] register pin %d with gpio %d with name %s\n", __FUNCTION__, i, hcsr04_gpio_pins[i].gpio, hcsr04_gpio_pins[i].name);
#endif
		err = gpio_request(hcsr04_gpio_pins[i].gpio, hcsr04_gpio_pins[i].name);
		if (err)
		{
#ifdef DEBUG
			printk("[%s] Could not get access to GPIO %i, error code: %i\n", __FUNCTION__, hcsr04_gpio_pins[i].gpio, err);
#endif
		}
		// only even pins are tiggers
		if (i % 2 == 0)
		{
			err = gpio_direction_output(hcsr04_gpio_pins[i].gpio, 0);
			if (err)
			{
#ifdef DEBUG
				printk("[%s] Could not set GPIO %i to output, error code: %i\n", __FUNCTION__, hcsr04_gpio_pins[i].gpio, err);
#endif
			}
		}
		// all odd pin are echos
		else
		{
			err = gpio_direction_input(hcsr04_gpio_pins[i].gpio);
			if (err)
			{
#ifdef DEBUG
				printk("[%s] Could not set GPIO %i to input, error code: %i\n", __FUNCTION__, hcsr04_gpio_pins[i].gpio, err);
#endif
			}
			/** for now do not use IRQs, for whatever reason this is way more unprecises then polling!!! **/
			// // also register interrupt for all echos
			// irq = gpio_to_irq(hcsr04_gpio_pins[i].gpio);
			// if (irq < 0)
			// {
			// 	printk("[%s] Could not register interrupt for GPIO %i, error code: %i\n", __FUNCTION__, hcsr04_gpio_pins[i].gpio, irq);
			// }
			// else
			// {
			// 	printk("[%s] Received GPIO interrupt %i for pin %i", __FUNCTION__, irq, hcsr04_gpio_pins[i].gpio);
			// 	err = request_irq(irq, MeasureISR, IRQF_TRIGGER_RISING, "IRQ_EDGE", (struct cdev *)&c_dev);
			// 	if (err)
			// 	{
			// 		printk("[%s] Registering of interrupt %i failed for rising edge, error code: %i\n", __FUNCTION__, irq, err);
			// 	}
			// 	printk("[%s] Set irq number %i\n", __FUNCTION__, irq);
			// 	hcsr04_gpio_pins[i].irq = irq;
			// }
		}
	}
// ready to go!
#ifdef DEBUG
	printk("[%s] HCSR04 device registered!\n", __FUNCTION__);
#endif
	return 0;
}

long hcsr04_control(struct file *f, unsigned int control, unsigned long value)
{
/*
	2DO!: Check why for HCSR04 no raw_copy_from_user is needed but st7565 needs it?!?
*/
#ifdef DEBUG
	printk("[%s] controlling: control = %x and value = %lx\n", __FUNCTION__, control, value);
#endif
	if (control == IOCTL_HCSR04_FL_TRIGGER)
	{
#ifdef DEBUG
		printk("[%s] Received read FL\n");
#endif
		return getDistanceFL();
	}
	if (control == IOCTL_HCSR04_FC_TRIGGER)
	{
#ifdef DEBUG
		printk("[%s] Received read FC\n");
#endif
		return getDistanceFC();
	}
	if (control == IOCTL_HCSR04_FR_TRIGGER)
	{
#ifdef DEBUG
		printk("[%s] Received read FR\n");
#endif
		return getDistanceFR();
	}
	if (control == IOCTL_HCSR04_RL_TRIGGER)
	{
#ifdef DEBUG
		printk("[%s] Received read RL\n");
#endif
		return getDistanceRL();
	}
	if (control == IOCTL_HCSR04_RR_TRIGGER)
	{
#ifdef DEBUG
		printk("[%s] Received read RR\n");
#endif
		return getDistanceRR();
	}
	return -1;
}

static int hcsr04_open(struct inode *i, struct file *f)
{
#ifdef DEBUG
	printk("[%s] opening hcsr04\n", __FUNCTION__);
#endif
	return 0;
}

static int hcsr04_close(struct inode *i, struct file *f)
{
#ifdef DEBUG
	printk("[%s] closing hcsr04\n", __FUNCTION__);
#endif
	return 0;
}

static ssize_t hcsr04_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
#ifdef DEBUG
	printk("[%s] length: %x\n", __FUNCTION__, len);
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

static ssize_t hcsr04_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	// fix access to *buf! copy from user space to kernel space first!
	buf = "HCSR04 returning string!!!";
	len = 27;
	return 0;
}

static void __exit hcsr04_deinit(void)
{
	int i;
#ifdef DEBUG
	printk("[%s] shutting down...", __FUNCTION__);
#endif
	// release buffer
	if (rx_buffer)
	{
		kfree(rx_buffer);
	}

	// release GPIO and interrupts
	for (i = 0; i < hcsr04_gpio_pin_info.num_pins; i++)
	{
		// unused since use of IRQs is disabled, due to efficiency!!
		if (hcsr04_gpio_pins[i].irq != 0)
		{
#ifdef DEBUG
			printk("[%s] Free irq number %i\n", __FUNCTION__, hcsr04_gpio_pins[i].irq);
#endif
			free_irq(hcsr04_gpio_pins[i].irq, (struct cdev *)&c_dev);
		}
		gpio_free(hcsr04_gpio_pins[i].gpio);
	}

	// unregister character device
	cdev_del(&c_dev);
	device_destroy(cl, second);
	class_destroy(cl);
	unregister_chrdev_region(second, 1);
#ifdef DEBUG
	printk("[%s] HCSR04 unregistered\n", __FUNCTION__);
#endif
}

int init_module(void)
{
	int i = 0;
#ifdef DEBUG
	printk("Hello World HCSR04!\n");
#endif
	hcsr04_init();
	// #ifdef DEBUG
	// 	printk("starting loop over all hcsr04 devices..\n");
	// 	for (i = 0; i < 20; i++)
	// 	{
	// 		getDistanceFL();
	// 		getDistanceFC();
	// 		getDistanceFR();
	// 		getDistanceRL();
	// 		getDistanceRR();
	// 		msleep(2000);
	// 	}
	// #endif
	return 0;
}

void cleanup_module(void)
{
	hcsr04_deinit();
#ifdef DEBUG
	printk("Goodbye Cruel World HCSR04!\n");
#endif
}

MODULE_LICENSE("GPL");

#endif // HCSR04_GPIO_C
