/*
 *
 */
#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <analogin_api.h>
#include <analogout_api.h>
#include <buffer.h>
#include <can_api.h>
#include <dma_api.h>
#include <ethernet_api.h>
#include <gpio_api.h>
#include <gpio_irq_api.h>
#include <i2c_api.h>
#include <lp_ticker_api.h>
#include <pinmap.h>
#include <port_api.h>
#include <pwmout_api.h>
#include <rtc_api.h>
#include <serial_api.h>
#include <sleep_api.h>
#include <spi_api.h>
#include <ticker_api.h>
#include <us_ticker_api.h>
#include <wait_api.h>

#ifndef bool
#define bool int
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

typedef unsigned char byte;

void arduino_init(void);

typedef enum pintype_e {
	pintype_none,
	pintype_gpio,
	pintype_dac,
	pintype_pwmout,
	pintype_analogin,
} PinType;

struct pin_node {
	struct pin_node *next;
	PinName pin;
	PinType type;
	union {
		gpio_t gpio;
#if DEVICE_ANALOGOUT
		dac_t dac;
#endif
		pwmout_t pwmout;
		analogin_t analogin;
	};
	uint32_t period;
	uint32_t pulsewidth;
	int min;
	int max;
};

/******************************************************/
/*  WRBB - SAKURAピン番コンバート */
/******************************************************/
struct pin_node *wrb2sakura(PinType type, PinName pinno);

PinType get_pin_type(PinName pin);

typedef enum sci_port {
	SCI_USB0,
	SCI_SCI0P2x,
	SCI_SCI2B,
	SCI_SCI6B,
	SCI_SCI2A,
} SCI_PORT;

bool portToPins(SCI_PORT port, PinName *txpin, PinName *rxpin);

extern serial_t *Serial;

int serial_write(serial_t *serial, const unsigned char *c, int len);
int serial_print(serial_t *serial, const char *c);
int serial_println(serial_t *serial, const char *c);

typedef struct File {
	int dummy;
} File;

#define FILE_READ 0x01
#define FILE_WRITE 0x02

int file_write(File *fd, unsigned char *str, int len);
int file_close(File *fd);
int file_size(File *fd);
int file_position(File *fd);
int file_flush(File *fd);
int file_seek(File *fd, int pos);
int file_read(File *fd);

typedef struct SDMMC {
	int dummy;
} SDMMC;

int SDMMC_begin(SDMMC *sdmmc);
File *SDMMC_open(SDMMC *sdmmc, const char *path, int mode);
bool SDMMC_rmdir(SDMMC *sdmmc, const char *path);
int SDMMC_rename(SDMMC *sdmmc, const char *path1, const char *path2);
int SDMMC_remove(SDMMC *sdmmc, const char *path);
bool SDMMC_exists(SDMMC *sdmmc, const char *path);
bool SDMMC_mkdir(SDMMC *sdmmc, const char *path);

typedef struct FILEEEP {
	int dummy;
} FILEEEP;

int EEP_fopen(FILEEEP *fp, const char *str, int mode);
void EEP_fwrite(FILEEEP *fp, byte *data, int *len);
int EEP_fread(FILEEEP *fp);
void EEP_fclose(FILEEEP *fp);
bool EEP_fseek(FILEEEP *fp, unsigned long pos, int mode);
unsigned long EEP_ffilesize(const char *str);
bool EEP_fEof(FILEEEP *fp);
bool EEP_fexist(const char *path);
bool EEP_fcopy(const char *src, const char *dst);

#define EEP_SEEKTOP 1
#define EEP_SEEKEND 3

#define EEP_READ 0x01
#define EEP_WRITE 0x02
#define EEP_APPEND 0x4

int EEPROM_write(unsigned long addr, unsigned char data);
unsigned char EEPROM_read(unsigned long addr);

#define REBOOT_USERAPP 1
void system_reboot(int mode);
int fileloader(const char *progVer, const char *binVer);

#endif /* _ARDUINO_H_ */
