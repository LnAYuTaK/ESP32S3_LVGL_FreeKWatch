#ifndef SD_FAT_H
#define SD_FAT_H
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
void initSdFat(void);
#define SD_CARD_PIN_MISO  GPIO_NUM_2
#define SD_CARD_PIN_MOSI  GPIO_NUM_15;
#define SD_CARD_PIN_CLK   GPIO_NUM_14;
#endif  //SD_FAT_H