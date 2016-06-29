#include <arduino.h>
#include <mruby.h>
#include "../llbruby.h"

serial_t *Serial;

void arduino_init()
{
	mbed_api_init();
}

struct pin_node *pin_list = NULL;

static struct pin_node *find_pin(PinType type, PinName pin)
{
	struct pin_node *ret = pin_list;

	while (ret != NULL) {
		if ((ret->type == type) && (ret->pin == pin)) {
			break;
		}
	}

	return ret;
}

static struct pin_node *new_pin(PinType type, PinName pin)
{
	struct pin_node *ret = calloc(1, sizeof(struct pin_node));

	ret->next = pin_list;
	ret->type = type;
	ret->pin = pin;

	pin_list->next = ret;

	return ret;
}

struct pin_node *wrb2sakura(PinType type, PinName pinno)
{
	int ret;
	struct pin_node *pin;

	switch (pinno) {
	case 0:
		ret = RB_PIN0;
		break;
	case 1:
		ret = RB_PIN1;
		break;
	case 2:
		ret = RB_PIN2;
		break;
	case 3:
		ret = RB_PIN3;
		break;
	case 4:
		ret = RB_PIN4;
		break;
	case 5:
		ret = RB_PIN5;
		break;
	case 6:
		ret = RB_PIN6;
		break;
	case 7:
		ret = RB_PIN7;
		break;
	case 8:
		ret = RB_PIN8;
		break;
	case 9:
		ret = RB_PIN9;
		break;
	case 10:
		ret = RB_PIN10;
		break;
	case 11:
		ret = RB_PIN11;
		break;
	case 12:
		ret = RB_PIN12;
		break;
	case 13:
		ret = RB_PIN13;
		break;
	case 14:
		ret = RB_PIN14;
		break;
	case 15:
		ret = RB_PIN15;
		break;
	case 16:
		ret = RB_PIN16;
		break;
	case 17:
		ret = RB_PIN17;
		break;
	case 18:
		ret = RB_PIN18;
		break;
	case 19:
		ret = RB_PIN19;
		break;

	case 20:
		ret = RB_PIN20;
		break;
	case 21:
		ret = RB_PIN21;
		break;
	case 22:
		ret = RB_PIN22;
		break;
	case 23:
		ret = RB_PIN23;
		break;
	case 24:
		ret = RB_PIN24;
		break;
	case 25:
		ret = RB_PIN25;
		break;

	default:
		return NULL;
	}

	pin = find_pin(type, ret);
	if (pin != NULL)
		return pin;

	pin = new_pin(type, ret);
	if (pin == NULL)
		return NULL;

	switch (type) {
	case pintype_gpio:
		gpio_init(&pin->gpio, ret);
		break;
	case pintype_dac:
		analogout_init(&pin->dac, ret);
		break;
	case pintype_pwmout:
		pwmout_init(&pin->pwmout, ret);
		pin->period = 491;
		break;
	case pintype_analogin:
		analogin_init(&pin->analogin, ret);
		break;
	}

	return pin;
}

bool portToPins(SCI_PORT port, PinName *txpin, PinName *rxpin)
{
	switch (port) {
	case SCI_USB0:
		*txpin = 201;
		*rxpin = 202;
		break;
	case SCI_SCI0P2x:
		*txpin = 1;
		*rxpin = 2;
		break;
	case SCI_SCI2B:
		*txpin = 1;
		*rxpin = 2;
		break;
	case SCI_SCI6B:
		*txpin = 1;
		*rxpin = 2;
		break;
	case SCI_SCI2A:
		*txpin = 1;
		*rxpin = 2;
		break;
	default:
		*txpin = 0;
		*rxpin = 0;
		return false;
	}

	return true;
}

PinType get_pin_type(PinName pin)
{
	struct pin_node *ret = pin_list;

	while (ret != NULL) {
		if (ret->pin == pin) {
			return ret->type;
		}
	}

	return pintype_none;
}

int EEPROM_write(unsigned long addr, unsigned char data)
{
	return 0;
}

unsigned char EEPROM_read(unsigned long addr)
{
	return 0;
}

int EEP_fopen(FILEEEP *fp, const char *str, int mode)
{
	return 0;
}

void EEP_fwrite(FILEEEP *fp, byte *data, int *len)
{

}

int EEP_fread(FILEEEP *fp)
{
	return 0;
}

void EEP_fclose(FILEEEP *fp)
{

}

bool EEP_fseek(FILEEEP *fp, unsigned long pos, int mode)
{
	return 0;
}

unsigned long EEP_ffilesize(const char *str)
{
	return 0;
}

bool EEP_fEof(FILEEEP *fp)
{
	return 0;
}

bool EEP_fexist(const char *path)
{
	return 0;
}

bool EEP_fcopy(const char *src, const char *dst)
{
	return 0;
}

int SDMMC_begin(SDMMC *sdmmc)
{
	return 0;
}

File *SDMMC_open(SDMMC *sdmmc, const char *path, int mode)
{
	return 0;
}

bool SDMMC_rmdir(SDMMC *sdmmc, const char *path)
{
	return 0;
}

int SDMMC_rename(SDMMC *sdmmc, const char *path1, const char *path2)
{
	return 0;
}

int SDMMC_remove(SDMMC *sdmmc, const char *path)
{
	return 0;
}

bool SDMMC_exists(SDMMC *sdmmc, const char *path)
{
	return 0;
}

bool SDMMC_mkdir(SDMMC *sdmmc, const char *path)
{
	return 0;
}

int file_write(File *fd, unsigned char *str, int len)
{
	return 0;
}

int file_close(File *fd)
{
	return 0;
}

int file_size(File *fd)
{
	return 0;
}

int file_position(File *fd)
{
	return 0;
}

int file_flush(File *fd)
{
	return 0;
}

int file_seek(File *fd, int pos)
{
	return 0;
}

int file_read(File *fd)
{
	return 0;
}

void system_reboot(int mode)
{

}

int fileloader(const char *progVer, const char *binVer)
{
	return 0;
}

void mrb_gr_sakura_gem_init(mrb_state *mrb)
{
}

void mrb_gr_sakura_gem_final(mrb_state *mrb)
{

}
