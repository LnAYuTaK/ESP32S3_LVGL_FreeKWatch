
//User
#include "LinkConfig.h"
#include "Application.h"
#include "LinkManager.h"
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
#include "background.c"
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
   
   lv_obj_t * icon = lv_img_create(lv_scr_act());
/*From variable*/
    LV_IMG_DECLARE(background );
    lv_img_set_src(icon, &background);
    app->appInit();
    for(;;) {
         lv_task_handler();
         lv_tick_inc(5);
         vTaskDelay(5);
     }


}
