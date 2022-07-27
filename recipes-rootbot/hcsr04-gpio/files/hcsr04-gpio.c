#ifndef HCSR04_GPIO_C
#define HCSR04_GPIO_C

#define LINUX
#define DEBUG

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>  /* for put_user */
#include <asm/errno.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#include "hcsr04-gpio.h"

static dev_t second; // Global variable for the second device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

static struct file_operations pugs_fops = { .owner = THIS_MODULE,
		.unlocked_ioctl = hcsr04_control, .write = hcsr04_write };

// Struct for each GPIO pin
struct gpio_pin {
	const char * name;
	unsigned gpio;
};

// Struct to point to all GPIO pins
struct gpio_platform_data {
	struct gpio_pin * pins;
	int num_pins;
};

// Struct for interface definition
static struct gpio_pin hcsr04_gpio_pins[] = 
{ 
	{ 
	.name = "hcsr04-trigger_FL", 
	.gpio = TRIGGER_FL, }, { 
	.name = "hcsr04-echo_FL", 
	.gpio = ECHO_FL, 
	}, {
	.name = "hcsr04-trigger_FC", 
	.gpio = TRIGGER_FC, }, { 
	.name = "hcsr04-echo_FC", 
	.gpio = ECHO_FC, 
	}, {
	.name = "hcsr04-trigger_FR", 
	.gpio = TRIGGER_FR, }, { 
	.name = "hcsr04-echo_FR", 
	.gpio = ECHO_FR, 
	}, {
	.name = "hcsr04-trigger_RR", 
	.gpio = TRIGGER_RR, }, { 
	.name = "hcsr04-echo_RR", 
	.gpio = ECHO_RR, 
	}, { 
	.name = "hcsr04-trigger_RL", 
	.gpio = TRIGGER_RL, }, { 
	.name = "hcsr04-echo_RL", 
	.gpio = ECHO_RL, },
};

static struct gpio_platform_data hcsr04_gpio_pin_info = { .pins =
		hcsr04_gpio_pins, .num_pins = ARRAY_SIZE(hcsr04_gpio_pins), };

// used for buffer
char * rx_buffer;
int BUFFER_SIZE = 5*4; // 4 bytes for each HCSR04 sensor

// trigger FL
int getDistanceFL(void){
	unsigned long start, end, duration;
	gpio_set_value(hcsr04_gpio_pins[0].gpio, 0);
	gpio_set_value(hcsr04_gpio_pins[1].gpio, 0);
	msleep(10);
	gpio_set_value(hcsr04_gpio_pins[0].gpio, 1);
	msleep(1);
	while(gpio_get_value(hcsr04_gpio_pins[1].gpio)!=1){
		// define exit strategy
	}
	start = ktime_get_ns();
	while(gpio_get_value(hcsr04_gpio_pins[1].gpio)!=0){
		// define exit strategy
	}
	end = ktime_get_ns();
	duration = end -start;
	printk("### first measurement: %lu #\n", duration);
	return 0;
}

// trigger FC
int getDistanceFC(void){
	return 2;
}

// trigger FR
int getDistanceFR(void){
	return 3;
}

// trigger LL
int getDistanceLL(void){
	return 4;
}

// trigger LR
int getDistanceLR(void){
	return 5;
}

// init GPIOs
static int __init chardev_init(void)
{
	int err, i;
	printk("[%s] initializiing GPIOs\n",__FUNCTION__);
	// allocate a buffer and zero it out
	rx_buffer = kmalloc(BUFFER_SIZE,  GFP_KERNEL);
	memset(rx_buffer, 0, BUFFER_SIZE);
#ifdef DEBUG
	printk("[%s] registering HCSR04-GPIO chr dev\n",__FUNCTION__);
#endif //DEBUG
	// register a character device
	if (alloc_chrdev_region(&second, 0, 1, "hcsr04") < 0)
	{
		#ifdef DEBUG
		printk("[%s] registering HCSR04-GPIO chr dev failed!!!\n",__FUNCTION__);
		#endif //DEBUG
		return -1;
	}
	// create sysfs class
	if ((cl = class_create(THIS_MODULE, "chardrv-gpio")) == NULL)
	{
		#ifdef DEBUG
		printk("[%s] registering HCSR04-GPIO sysfs class failed!!!\n",__FUNCTION__);
		#endif //DEBUG
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] creating HCSR04-GPIO device\n",__FUNCTION__);
#endif //DEBUG
	if (device_create(cl, NULL, second, NULL, "hcsr04") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] HCSR04_GPIO cdev init\n",__FUNCTION__);
#endif //DEBUG
	cdev_init(&c_dev, &pugs_fops);
	if (cdev_add(&c_dev, second, 1) == -1)
	{
		device_destroy(cl, second);
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}

	// request access to GPIO, set them all as outputs (initially low)
	printk("[%s] registering HCSR04_GPIO pins\n",__FUNCTION__);
	for(i = 0; i < hcsr04_gpio_pin_info.num_pins; i++) {
		printk("[%s] register pin %d with gpio %d with name %s\n",__FUNCTION__,i,hcsr04_gpio_pins[i].gpio, hcsr04_gpio_pins[i].name);
		err = gpio_request(hcsr04_gpio_pins[i].gpio, hcsr04_gpio_pins[i].name);
		if(err) {
			printk("[%s] Could not get access to GPIO %i, error code: %i\n",__FUNCTION__, hcsr04_gpio_pins[i].gpio, err);
		}
		err = gpio_direction_output(hcsr04_gpio_pins[i].gpio, 0);
		if(err) {
			printk("[%s] Could not set value of GPIO %i, error code: %i\n",__FUNCTION__, hcsr04_gpio_pins[i].gpio, err);
		}
	}
	// ready to go!
	printk("[%s] HCSR04 registered!\n",__FUNCTION__);

	return 0;
}

int gpio_init_test(void){
	printk("First test!!!\n");
	getDistanceFL();
	printk("done..\n");
	return 0;
}

long hcsr04_control(struct file *f, unsigned int control, unsigned long value) {
#ifdef DEBUG
	printk("[%s] controlling: control = %x and value = %lx\n",__FUNCTION__, control, value);
#endif
	printk("#### also without DEBUG flag in control\n");
	return 0;
}

static ssize_t hcsr04_write(struct file *f, const char __user *buf, size_t len, loff_t *off) {
#ifdef DEBUG
	printk("[%s] start printing: %s\n",__FUNCTION__,buf);
#endif
	printk("#### also without DEBUG flag in write\n");
	return len;
}

static void __exit hcsr04_exit(void)
{
	int i;
	printk("[%s] shutting down...",__FUNCTION__);
	// release buffer
	if (rx_buffer) {
		kfree(rx_buffer);
	}

	// release GPIO
	for(i = 0; i < hcsr04_gpio_pin_info.num_pins; i++) {
		gpio_free(hcsr04_gpio_pins[i].gpio);
	}

	// unregister character device
	cdev_del(&c_dev);
	device_destroy(cl, second);
	class_destroy(cl);
	unregister_chrdev_region(second, 1);
	printk("[%s] HCSR04 unregistered\n",__FUNCTION__);
}

int init_module(void)
{
	printk("Hello World HCSR04!\n");
	chardev_init();
	gpio_init_test();
	return 0;
}

void cleanup_module(void)
{
	hcsr04_exit();
	printk("Goodbye Cruel World HCSR04!\n");
}

MODULE_LICENSE("GPL");

#endif // HCSR04_GPIO_C
