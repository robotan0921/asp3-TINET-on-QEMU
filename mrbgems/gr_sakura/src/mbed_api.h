/*
 *
 */
#ifndef _MBED_API_H_
#define _MBED_API_H_

void mbed_api_init(void);

void wait_ms(int ms);
uint32_t us_ticker_read(void);

typedef enum {
	PIN_LED0 = 100,
	PIN_LED1,
	PIN_LED2,
	PIN_LED3,
} PinName;

typedef enum {
	PIN_INPUT,
	PIN_OUTPUT
} PinDirection;

typedef enum {
	PullUp = 0,
	PullDown = 3,
	PullNone = 2,
	OpenDrain = 4,
	PullDefault = PullDown
} PinMode;

typedef struct gpio_s {
	PinName  pin;
} gpio_t;

void gpio_init(gpio_t *obj, PinName pin);
void gpio_mode(gpio_t *obj, PinMode mode);
void gpio_dir(gpio_t *obj, PinDirection direction);

void gpio_write(gpio_t *obj, int value);
int gpio_read(gpio_t *obj);

void gpio_init_in(gpio_t* gpio, PinName pin);
void gpio_init_out(gpio_t* gpio, PinName pin);

typedef struct analogin_s {
	PinName pin;
} analogin_t;

void analogin_init(analogin_t *obj, PinName pin);
uint16_t analogin_read_u16(analogin_t *obj);

typedef struct dac_s {
	PinName pin;
} dac_t;

void analogout_init(dac_t *obj, PinName pin);
void analogout_write_u16(dac_t *obj, uint16_t value);

typedef struct pwmout_s {
	PinName pin;
} pwmout_t;

void pwmout_init(pwmout_t* obj, PinName pin);
void pwmout_free(pwmout_t* obj);

void pwmout_period_us(pwmout_t* obj, int us);
void pwmout_pulsewidth_us(pwmout_t* obj, int us);

typedef enum {
    ParityNone = 0,
    ParityOdd = 1,
    ParityEven = 2,
    ParityForced1 = 3,
    ParityForced0 = 4
} SerialParity;

typedef enum {
    FlowControlNone,
    FlowControlRTS,
    FlowControlCTS,
    FlowControlRTSCTS
} FlowControl;

typedef struct serial_s {
	int dummy;
} serial_t;

void serial_init(serial_t *obj, PinName tx, PinName rx);
void serial_free(serial_t *obj);
void serial_baud(serial_t *obj, int baudrate);
void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits);
int serial_getc(serial_t *obj);
void serial_putc(serial_t *obj, int c);
int serial_readable(serial_t *obj);
int serial_writable(serial_t *obj);

typedef struct i2c_s {
	unsigned char rxdata[16];
} i2c_t;

void i2c_init(i2c_t *obj, PinName sda, PinName scl);
void i2c_frequency(i2c_t *obj, int hz);
int i2c_start(i2c_t *obj);
int i2c_stop(i2c_t *obj);
int i2c_read(i2c_t *obj, int address, char *data, int length, int stop);
int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop);
int i2c_byte_read(i2c_t *obj, int last);
int i2c_byte_write(i2c_t *obj, int data);

void rtc_init(void);
void rtc_free(void);
int rtc_isenabled(void);
time_t rtc_read(void);
void rtc_write(time_t t);

#endif /* _MBED_API_H_ */
