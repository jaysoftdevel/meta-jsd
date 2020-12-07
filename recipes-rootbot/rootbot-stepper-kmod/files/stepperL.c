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

#define DEBUG

/* Kernel Programming */
//#define MODULE
#define LINUX
//#define __KERNEL__

//#if defined(CONFIG_MODVERSIONS) && ! defined(MODVERSIONS)
//   #include <linux/modversions.h>
//   #define MODVERSIONS
//#endif
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
                   
#include "stepperL.h"


static struct tPos coilPos;

#ifdef TESTSTEPPER
//int main(void) {
	//int delay=DELAY;
	//// init gpio
//#ifdef DEBUG
	//printk("setup gpio\n");
//#endif
	//initStepperLGpio();
	//int i = 0;
//#ifdef DEBUG
	//printk("wait to get started\n");
//#endif
	//usleep(2000000);
//#ifdef DEBUG
	//printk("start...\n");
//#endif
	//for (i; i < CYCLES; i++) {
		////printk("rtp %i delay: %i\n",i,delay);
		//// roundtippin
		//pin_high(PORT_P8, COIL_PIN_NORTH);
		//pin_low(PORT_P8, COIL_PIN_EAST);
		//pin_low(PORT_P8, COIL_PIN_SOUTH);
		//pin_low(PORT_P8, COIL_PIN_WEST);
		//usleep(delay);
		//pin_low(PORT_P8, COIL_PIN_NORTH);
		//pin_high(PORT_P8, COIL_PIN_EAST);
		//pin_low(PORT_P8, COIL_PIN_SOUTH);
		//pin_low(PORT_P8, COIL_PIN_WEST);
		//usleep(delay);
		//pin_low(PORT_P8, COIL_PIN_NORTH);
		//pin_low(PORT_P8, COIL_PIN_EAST);
		//pin_high(PORT_P8, COIL_PIN_SOUTH);
		//pin_low(PORT_P8, COIL_PIN_WEST);
		//usleep(delay);
		//pin_low(PORT_P8, COIL_PIN_NORTH);
		//pin_low(PORT_P8, COIL_PIN_EAST);
		//pin_low(PORT_P8, COIL_PIN_SOUTH);
		//pin_high(PORT_P8, COIL_PIN_WEST);
		//usleep(delay);
	//}
	//pin_low(PORT_P8, COIL_PIN_NORTH);
	//pin_low(PORT_P8, COIL_PIN_EAST);
	//pin_low(PORT_P8, COIL_PIN_SOUTH);
	//pin_low(PORT_P8, COIL_PIN_WEST);
	//// deinit gpio
//#ifdef DEBUG
	//printk("done roundtripping, deiniting...\n");
//#endif
	//deinitStepperLGpio();
	//return (0);
//}
#endif /*TESTSTEPPER*/

int stepFwdL(void) {
	int i;
	for(i=0;i<NUM_OF_COILS;i++){
#ifdef DEBUG
		printk("i: %i coil: %i\n",i,coilPos.pos);
#endif
		if(i!=coilPos.pos){
#ifdef DEBUG
			printk("set pin %i low\n",COIL_PIN_OFFSET+i);
#endif
			//pin_low(PORT_P8, COIL_PIN_OFFSET+i);
			gpio_set_value(COIL_PIN_OFFSET+i, 0);
		}
		else{
#ifdef DEBUG
			printk("set pin %i high\n",COIL_PIN_OFFSET+coilPos.pos);
#endif
			//pin_high(PORT_P8, COIL_PIN_OFFSET+coilPos.pos);
			gpio_set_value(COIL_PIN_OFFSET+coilPos.pos, 1);
		}
	}
	coilPos.pos++;
	return (0);
}

int stepRevL(void) {
	int i;
	for(i=0;i<NUM_OF_COILS;i++){
#ifdef DEBUG
		printk("i: %i coil: %i\n",i,coilPos.pos);
#endif
		if(i!=coilPos.pos){
#ifdef DEBUG
			printk("set pin %i low\n",COIL_PIN_OFFSET+i);
#endif
			//pin_low(PORT_P8, COIL_PIN_OFFSET+i);
			gpio_set_value(COIL_PIN_OFFSET+i, 0);
		}
		else{
#ifdef DEBUG
			printk("set pin %i high\n",COIL_PIN_OFFSET+coilPos.pos);
#endif
			//pin_high(PORT_P8, COIL_PIN_OFFSET+coilPos.pos);
			gpio_set_value(COIL_PIN_OFFSET+coilPos.pos, 1);
		}
	}
	coilPos.pos--;
	return (0);
}

int stepLNone(void){
	//pin_low(PORT_P8, COIL_PIN_NORTH);
	//pin_low(PORT_P8, COIL_PIN_EAST);
	//pin_low(PORT_P8, COIL_PIN_SOUTH);
	//pin_low(PORT_P8, COIL_PIN_WEST);
	printk("set all pint to low\n");
	gpio_set_value(COIL_PIN_NORTH, 0);
	gpio_set_value(COIL_PIN_EAST, 0);
	gpio_set_value(COIL_PIN_SOUTH, 0);
	gpio_set_value(COIL_PIN_WEST, 0);
}
/**
 *
 * move this function to a global util library for this project
 *
 **/
//void setGPIOClock() {
//	int fd = open("/dev/mem", O_RDWR | O_SYNC);
//	if (fd < 0) {
//		printk("Could not open GPIO memory fd\n");
//		return;
//	}
//
//	unsigned int *clock_gpio2;
//	clock_gpio2 = (unsigned int *) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
//			MAP_SHARED, fd, 0x44E00000);
//	// 0xb0 is CM_PER_GPIO2_CLKCTRL as given in the TRM, use 0xb4 for GPIO_3 (see the TRM)
//	int offsetInMemory = 0xb0;
//	// get the value, we divide by 4 because it is a byte offset
//	int memValue = clock_gpio2[(offsetInMemory / 4)];
//#ifdef DEBUG
//	// print it – it will probably be 0x030000 if the clock has never been enabled
//	printk("Value = %04x\n", memValue);
//#endif
//	// now set it, this enables the memory
//	clock_gpio2[(offsetInMemory / 4)] = 0x02;
//	close(fd);
//
//}


//int initStepperLGpio() {

//#ifdef DEBUG
	//printk("setting up pins\n");
//#endif
	//if (iolib_setdir(PORT_P8, COIL_PIN_NORTH, DIR_OUT)) {
		//printk("could not set pin %i on port %i with direction %i\n",
				//COIL_PIN_NORTH, PORT_P8, DIR_OUT);
		//return (-2);
	//}
	//if (iolib_setdir(PORT_P8, COIL_PIN_EAST, DIR_OUT)) {
		//printk("could not set pin %i on port %i with direction %i\n",
				//COIL_PIN_EAST, PORT_P8, DIR_OUT);
		//return (-2);
	//}
	//if (iolib_setdir(PORT_P8, COIL_PIN_SOUTH, DIR_OUT)) {
		//printk("could not set pin %i on port %i with direction %i\n",
				//COIL_PIN_SOUTH, PORT_P8, DIR_OUT);
		//return (-2);
	//}
	//if (iolib_setdir(PORT_P8, COIL_PIN_WEST, DIR_OUT)) {
		//printk("could not set pin %i on port %i with direction %i\n",
				//COIL_PIN_WEST, PORT_P8, DIR_OUT);
		//return (-2);
	//}
	//pin_low(PORT_P8, COIL_PIN_NORTH);
	//pin_low(PORT_P8, COIL_PIN_EAST);
	//pin_low(PORT_P8, COIL_PIN_SOUTH);
	//pin_low(PORT_P8, COIL_PIN_WEST);
//#ifdef DEBUG
	//printk("pins ok\n");
//#endif

	//return (0);
//}

//int deinitStepperLGpio() {
	//iolib_free();
	//return (0);
//}

long stepperL_control(struct file *f, unsigned int control, unsigned long value);
static ssize_t stepperL_write(struct file *f, const char __user *buf, size_t len, loff_t *off);

static dev_t second; // Global variable for the second device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

static struct file_operations pugs_fops = { .owner = THIS_MODULE,
		.unlocked_ioctl = stepperL_control, .write = stepperL_write };
		
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
static struct gpio_pin stepperL_gpio_pins[] = { { .name = "stepperL::north", .gpio =
COIL_PIN_NORTH, }, { .name = "stepperL::east", .gpio = COIL_PIN_EAST, }, { .name =
		"stepperL::south", .gpio = COIL_PIN_SOUTH, }, { .name = "stepperL::west", .gpio =
COIL_PIN_WEST, }, };

static struct gpio_platform_data stepperL_gpio_pin_info = { .pins =
		stepperL_gpio_pins, .num_pins = ARRAY_SIZE(stepperL_gpio_pins), };


// used for buffer
char * rx_buffer;
int BUFFER_SIZE = 8;

static int __init stepperL_init(void)
{
	printk("[%s] initializiing stepperL\n",__FUNCTION__);
	// allocate a buffer and zero it out
	rx_buffer = kmalloc(BUFFER_SIZE,  GFP_KERNEL);
	memset(rx_buffer, 0, BUFFER_SIZE);
#ifdef DEBUG
	printk("[%s] registering stepperL chr dev\n",__FUNCTION__);
#endif //DEBUG
	// register a character device
	if (alloc_chrdev_region(&second, 0, 1, "stepperL") < 0)
			{
				return -1;
			}
			if ((cl = class_create(THIS_MODULE, "chardrv2")
	) == NULL)
	{
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] creating stepperL device\n",__FUNCTION__);
#endif //DEBUG
	if (device_create(cl, NULL, second, NULL, "stepperL") == NULL)
	{
		class_destroy(cl);
		unregister_chrdev_region(second, 1);
		return -1;
	}
#ifdef DEBUG
	printk("[%s] stepperL cdev init\n",__FUNCTION__);
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
	printk("[%s] registering stepperL gpio pins\n",__FUNCTION__);
	int err, i;
	i = 0;
	for(i = 0; i < stepperL_gpio_pin_info.num_pins; i++) {
		printk("[%s] register pin %d with gpio %d with name %s\n",__FUNCTION__,i,stepperL_gpio_pins[i].gpio, stepperL_gpio_pins[i].name);
		err = gpio_request(stepperL_gpio_pins[i].gpio, stepperL_gpio_pins[i].name);
		if(err) {
			printk("[%s] Could not get access to GPIO %i, error code: %i\n",__FUNCTION__, stepperL_gpio_pins[i].gpio, err);
		}
		err = gpio_direction_output(stepperL_gpio_pins[i].gpio, 0);
		if(err) {
			printk("[%s] Could not set value of GPIO %i, error code: %i\n",__FUNCTION__, stepperL_gpio_pins[i].gpio, err);
		}
	}
	// ready to go!
	printk("[%s] stepperL registered!\n",__FUNCTION__);

	return 0;
}

long stepperL_control(struct file *f, unsigned int control, unsigned long value) {
#ifdef DEBUG
	printk("[%s] controlling\n",__FUNCTION__);
#endif
	return 0;
}

static ssize_t stepperL_write(struct file *f, const char __user *buf, size_t len, loff_t *off) {
#ifdef DEBUG
	printk("[%s] start printing\n",__FUNCTION__);
#endif

return len;
}

static void __exit stepperL_exit(void)
{
	printk("[%s] shutting down...",__FUNCTION__);
	// release buffer
	if (rx_buffer) {
		kfree(rx_buffer);
	}

	// release GPIO
	int i = 0;
	for(i = 0; i < stepperL_gpio_pin_info.num_pins; i++) {
		gpio_free(stepperL_gpio_pins[i].gpio);
	}

	// unregister character device
	cdev_del(&c_dev);
	device_destroy(cl, second);
	class_destroy(cl);
	unregister_chrdev_region(second, 1);
	printk("[%s] stepperL unregistered\n",__FUNCTION__);
}

/********************/

int init_module(void)
{
	printk("Hello World stepperL!\n");
	stepperL_init();
	msleep(1000);
	stepFwdL();
	msleep(1000);
	stepFwdL();
	//msleep(1000);
	//stepLNone();
	return 0;
}

void cleanup_module(void)
{
	stepperL_exit();
	printk("Goodbye Cruel World stepperL!\n");
}

MODULE_LICENSE("GPL");

#endif /* STEPPERMOTOR_CONTROL_L_H */
