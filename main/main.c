#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lv_port_disp.c"
#include "lv_port_indev.h"
#include "lv_fs_if.h"
#include "wifi.h"
#include "MainPage.c"
#include "esp_system.h"
#include <string.h>
static const char *TAG = "Main";
void app_main(void) 
{
    //网络wifi 时钟初始化//
    netInit();
    //lvgl 初始化//
    lv_init();
    //显示设备初始化
    lv_port_disp_init();
    //文件系统初始化
    //lv_fs_if_init();
    //输入设备初始化
    lv_port_indev_init();
    //应用层页面组件初始化
    PageInit();
    for(;;) {
         lv_task_handler();
         lv_tick_inc(5);
         vTaskDelay(5);
     }
}
