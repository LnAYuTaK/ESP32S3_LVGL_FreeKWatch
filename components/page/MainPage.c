/*********************
 *      INCLUDES
*********************/
#include "MainPage.h"
#include "lv_port_indev.h"
#include "WifiPage.h"
#include "MusicPage.h"
#include "MainPageControl.h"
#include "BGIMG.c"
#include "esp_log.h"
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
lv_obj_t * musicPage;


/**********************
 *      FUNCTION
 **********************/
void PageInit()
{
    //主界面初始化
    static lv_style_t Style;
    lv_style_init(&Style);
    page_manager = lv_100ask_page_manager_create(lv_scr_act());
    //背景图
    // lv_style_set_bg_img_src(&Style,&BGIMG); 
    // lv_style_set_bg_img_opa(&Style,LV_OPA_COVER);
    lv_obj_add_style(page_manager, &Style, 0);
    //Main界面
    main_page = lv_100ask_page_manager_page_create(page_manager, "Main_page");
    lv_100ask_page_manager_set_page_init(main_page,initMainPage);
    //WIFI界面初始化
    wifiPage = lv_100ask_page_manager_page_create(page_manager, "Wifi_page");
    lv_100ask_page_manager_set_page_init(wifiPage,initWifiPage);
    //Music界面初始化
    musicPage= lv_100ask_page_manager_page_create(page_manager, "Music_page");
    lv_100ask_page_manager_set_page_init(musicPage,initMusicPage);
    //
    lv_100ask_page_manager_set_main_page(page_manager, main_page);
    lv_100ask_page_manager_set_open_page(NULL, "Main_page");
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//主界面初始化
void initMainPage(lv_obj_t * page)
{
    //显示时间
    lv_obj_t * timeClock =  clockControl(page);
    lv_obj_align(timeClock, LV_ALIGN_TOP_MID, 0,30);
    //中间滚动条
    lv_obj_t * scrollbar  = scrollBarControl(page); 
    lv_obj_center(scrollbar);
}

