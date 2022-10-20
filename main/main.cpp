
//User
#include "LinkConfig.h"
#include "Application.h"
#include "LinkManager.h"
//FreeRtos
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lv_port_disp.c"
#include "lv_fs_if.h"
extern "C"
{
#include "wifi.h"
}

extern "C" void app_main(void) 
{

    lv_init();
    lv_port_disp_init();
    // lv_fs_if_init();
    //wifi配置初始化
    // init_nvs();
    // wifi_init_sta();
    //应用层组件初始化
    Application* app = new Application();
    app->appInit();
    for(;;) {
         lv_task_handler();
         lv_tick_inc(5);
         vTaskDelay(5);
     }


}
