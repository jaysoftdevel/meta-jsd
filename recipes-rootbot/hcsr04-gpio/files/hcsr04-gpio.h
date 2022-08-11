#ifndef HCSR04_GPIO_H
#define HCSR04_GPIO_H

// macro to convert bank and gpio into pin number
#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))

// Data and control lines
#define TRIGGER_FL	GPIO_TO_PIN(2, 10)	// P8_41, grey
#define ECHO_FL		GPIO_TO_PIN(2, 7)	// P8_46  grey

#define TRIGGER_FC	GPIO_TO_PIN(2, 13)	// P8_40, white
#define ECHO_FC		GPIO_TO_PIN(2, 6)	// P8_45, white

#define TRIGGER_FR	GPIO_TO_PIN(2, 12)	// P8_39, black
#define ECHO_FR		GPIO_TO_PIN(0, 11)	// P8_32, black, instead of P8_44 which is a boot pin!

#define TRIGGER_RL	GPIO_TO_PIN(2, 15)	// P8_38, brown
#define ECHO_RL		GPIO_TO_PIN(2, 8)	// P8_43, brown

#define TRIGGER_RR	GPIO_TO_PIN(2, 14)	// P8_37, red
#define ECHO_RR		GPIO_TO_PIN(2, 11)	// P8_42, red

static int hcsr04_open(struct inode *i, struct file *f);
static ssize_t hcsr04_read(struct file *f, char __user *buf, size_t len, loff_t *off);
long hcsr04_control(struct file *f, unsigned int control, unsigned long value);
static ssize_t hcsr04_write(struct file *f, const char __user *buf, size_t len, loff_t *off);
static int hcsr04_close(struct inode *i, struct file *f);
long echoToDistance(long duration);

// Interrupts not used, too unprecise!
//static irqreturn_t MeasureISR(int irq, void *dev);

int getDistanceFL(void);
int getDistanceFC(void);
int getDistanceFR(void);
int getDistanceRL(void);
int getDistanceRR(void);

#endif // HCSR04_GPIO_H
