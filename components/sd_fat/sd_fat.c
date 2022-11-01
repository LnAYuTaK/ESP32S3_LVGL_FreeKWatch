
#include "sd_fat.h"
//初始化文件系统
static const char *SDFAT = "SDCard";
esp_err_t initSdFat(void)
{
    esp_err_t ret;
    sdmmc_card_t *card;//SD卡信息结构
    //文件系统挂载配置
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {

        //挂载失败就不会重新分区格式化
        .format_if_mount_failed = false,
        //打开文件最大数量
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(SDFAT, "Initializing SD card");

    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    ESP_LOGI(SDFAT, "Using SPI peripheral");

    //SD SPI 主机默认属性配置
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    //修改VSPI_HOST
    host.slot = SPI3_HOST;
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz =4*1024*sizeof(uint8_t),
    };
    //SPI总线初始化  DMA自动分配
    ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(SDFAT, "Failed to initialize bus.");
        return ret;
    }
    //SD SPI设备配置
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;  //CS片选
    slot_config.gpio_cd = PIN_NUM_CD;  //SD插拔检测信号线
    slot_config.host_id = host.slot;   //主机ID
    //挂载文件系统
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(SDFAT, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(SDFAT, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }
    ESP_LOGI(SDFAT, "Filesystem mounted");
    sdmmc_card_print_info(stdout, card);
    return ESP_OK;
}