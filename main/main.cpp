
//SYS
#include <iostream>
//User
#include "LinkConfig.h"
#include "Application.h"
#include "LinkManager.h"
#include "esp_event_cxx.h"
//FreeRtos
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
extern "C"
{
#include "lvgl.h"
#include "lv_port_disp.c"
#include "lv_fs_if.h"
#include "wifi.h"
}
extern "C" void app_main(void)
{
    //初始化LVGL
    Application* app = new Application();
    lv_init();
    init_nvs();
    wifi_init_sta();
    //初始化LVGL显示端口
    lv_port_disp_init();
    //初始化文件系统
    //lv_fs_if_init();
    ESPEventID id(2);
   

    app->appInit();
    for(;;) {
        lv_task_handler();
        lv_tick_inc(10);
        vTaskDelay(10);
    }
    
}
