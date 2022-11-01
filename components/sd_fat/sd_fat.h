#ifndef SD_FAT_H
#define SD_FAT_H
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#define MOUNT_POINT "/sdcard"
//VSPI
#define PIN_NUM_MISO  37
#define PIN_NUM_MOSI  35
#define PIN_NUM_CLK   36
#define PIN_NUM_CS    39
#define PIN_NUM_CD    34   
esp_err_t initSdFat(void);
#endif  //SD_FAT_H