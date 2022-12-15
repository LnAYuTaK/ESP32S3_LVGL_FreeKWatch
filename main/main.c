#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lv_port_disp.c"
#include "lv_port_indev.h"
#include "lv_fs_if.h"
#include "wifi.h"
#include "MainPage.h"
#include "esp_system.h"
#include <string.h>
#include "stdio.h"
static void lv_tick_task(void *arg)
{
	(void)arg;
	lv_tick_inc(10);
}
void app_main(void) 
{
    //网络wifi 时钟初始化//
    //netInit();
    //lvgl 初始化//
    lv_init();
    //显示设备初始化
    lv_port_disp_init();
    //文件系统初始化
    lv_fs_if_init();
    //输入设备初始化
    lv_port_indev_init();
    //应用层组件初始化
    //初始化LVGL时钟
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));
    PageInit();
    for(;;) {
         lv_task_handler();
         vTaskDelay(pdMS_TO_TICKS(10));
     }
}
