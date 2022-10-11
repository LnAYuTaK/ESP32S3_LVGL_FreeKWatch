#include <iostream>
#include "LinkConfig.h"
#include "Application.h"
#include "LinkManager.h"
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"
#include  "lvgl.h"
#include "lv_port_disp.c"
#include "lv_fs_if.h"
#ifdef __cplusplus
}
#endif
extern "C" void app_main(void)
{
    //初始化LVGL
    Application* app = new Application();
   lv_init();
   //初始化LVGL显示端口
   lv_port_disp_init();
   //初始化文件系统
   lv_fs_if_init();
    app->appInit();
    for(;;)
    {
        lv_task_handler();
        lv_tick_inc(10);
        vTaskDelay(10);
    }
    
}
