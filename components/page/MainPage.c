/*********************
 *      INCLUDES
*********************/
#include "MainPage.h"
#include "lv_port_indev.h"
#include "WifiPage.h"
#include "MainPageControl.h"
#include "BGIMG.c"
/*********************
 *      BGIMG
*********************/
LV_IMG_DECLARE(BGIMG)
/*********************
 *      DEFINES
 *********************/
lv_obj_t * page_manager;
lv_obj_t * main_page;
lv_obj_t * wifiPage;
/**********************
 *      FUNCTION
 **********************/
void PageInit()
{
    //主界面初始化
    static lv_style_t Style;
    lv_style_init(&Style);
    page_manager = lv_100ask_page_manager_create(lv_scr_act());
    lv_style_set_bg_img_opa(&Style,LV_OPA_COVER);
    //背景图
    lv_style_set_bg_img_src(&Style,&BGIMG); 
    lv_obj_add_style(page_manager, &Style, 0);
    main_page = lv_100ask_page_manager_page_create(page_manager, "Main_page");
    lv_100ask_page_manager_set_page_init(main_page,initMainPage);
    //WIFI界面初始化
    wifiPage = lv_100ask_page_manager_page_create(page_manager, "Wifi_page");
    lv_100ask_page_manager_set_page_init(wifiPage,initWifiPage);
    lv_100ask_page_manager_set_main_page(page_manager, main_page);
    lv_100ask_page_manager_set_open_page(NULL, "Main_page");
}

//主界面初始化
void initMainPage(lv_obj_t * page)
{
    //状态栏图标栏
    
    //中间滚动条
    scrollBarControl(page);
    //时间控件
    clockControl(page);
    //滑动解锁
} 







