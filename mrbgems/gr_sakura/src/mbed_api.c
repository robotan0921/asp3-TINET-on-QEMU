/*
 *
 */
#include <stdint.h>
#include <time.h>
#include <mbed_api.h>

void mbed_api_init()
{

}

void wait_ms(int ms)
{
}

uint32_t us_ticker_read(void)
{
	return 0;
}

void gpio_init(gpio_t *obj, PinName pin)
{
}

void gpio_mode(gpio_t *obj, PinMode mode)
{
}

void gpio_dir(gpio_t *obj, PinDirection direction)
{
}

void gpio_write(gpio_t *obj, int value)
{
}

int gpio_read(gpio_t *obj)
{
	return 0;
}

void gpio_init_in(gpio_t* gpio, PinName pin)
{
}

void gpio_init_out(gpio_t* gpio, PinName pin)
{
}

void analogin_init(analogin_t *obj, PinName pin)
{
}

uint16_t analogin_read_u16(analogin_t *obj)
{
	return 0;
}

void analogout_init(dac_t *obj, PinName pin)
{
}

void analogout_write_u16(dac_t *obj, uint16_t value)
{
}

void pwmout_init(pwmout_t* obj, PinName pin)
{
}

void pwmout_free(pwmout_t* obj)
{
}

void pwmout_period_us(pwmout_t* obj, int us)
{
}

void pwmout_pulsewidth_us(pwmout_t* obj, int us)
{
}

void serial_init(serial_t *obj, PinName tx, PinName rx)
{
}

void serial_free(serial_t *obj)
{
}

void serial_baud(serial_t *obj, int baudrate)
{
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{
}

int serial_getc(serial_t *obj)
{
	return 0;
}

void serial_putc(serial_t *obj, int c)
{
}

int serial_readable(serial_t *obj)
{
	return 0;
}

int serial_writable(serial_t *obj)
{
	return 0;
}

void i2c_init(i2c_t *obj, PinName sda, PinName scl)
{
}

void i2c_frequency(i2c_t *obj, int hz)
{
}

int i2c_start(i2c_t *obj)
{
	return 0;
}

int i2c_stop(i2c_t *obj)
{
	return 0;
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop)
{
	return 0;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop)
{
	return 0;
}

int i2c_byte_read(i2c_t *obj, int last)
{
	return 0;
}

int i2c_byte_write(i2c_t *obj, int data)
{
	return 0;
}

void rtc_init(void)
{
}

void rtc_free(void)
{
}

int rtc_isenabled(void)
{
	return 0;
}

time_t rtc_read(void)
{
	return 0;
}

void rtc_write(time_t t)
{
}

