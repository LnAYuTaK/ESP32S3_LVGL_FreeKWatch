#include <iostream>
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include  "lvgl.h"
#include "lv_port_disp.c"
#ifdef __cplusplus
}
#endif
extern "C" void app_main(void)
{

    //初始化LVGL
    lv_init();
    lv_port_disp_init();

    //初始化WIFI

    //初始化串口
    for(;;)
    {
        lv_task_handler();
        lv_tick_inc(10);
        vTaskDelay(10);
    }
    
}
