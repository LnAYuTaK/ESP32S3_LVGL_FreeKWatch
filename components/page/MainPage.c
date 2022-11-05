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

static mainGroup_t mainGroup;

/**********************
 *      FUNCTION
 **********************/
void PageInit()
{
    //主界面初始化
    static lv_style_t Style;
    lv_style_init(&Style);
    page_manager = lv_100ask_page_manager_create(lv_scr_act());
    lv_style_set_bg_color(&Style,lv_color_black());
    lv_style_set_bg_opa(&Style,LV_OPA_COVER);
    //背景图
    // lv_style_set_bg_img_src(&Style,&BGIMG); 
    // lv_style_set_bg_img_opa(&Style,LV_OPA_COVER);
    lv_obj_add_style(page_manager, &Style, 0);
    //Main界面
    main_page = lv_100ask_page_manager_page_create(page_manager, "Main_page");
    lv_100ask_page_manager_set_page_init(main_page,initMainPage);
    lv_100ask_page_manager_set_page_group_load(main_page,mainGroupLoad);
    //WIFI界面初始化
    wifiPage = lv_100ask_page_manager_page_create(page_manager, "Wifi_page");
    lv_100ask_page_manager_set_page_init(wifiPage,initWifiPage);
    lv_100ask_page_manager_set_page_group_load(wifiPage,wifiGroupLoad);
    //Music界面初始化
    musicPage= lv_100ask_page_manager_page_create(page_manager, "Music_page");
    lv_100ask_page_manager_set_page_init(musicPage,initMusicPage);
    //
    lv_100ask_page_manager_set_main_page(page_manager, main_page);
    lv_100ask_page_manager_set_open_page(NULL, "Main_page");
}
//-----------------------------------------------------------------------------
void mainGroupLoad(lv_obj_t * page)
{
 ESP_LOGE("MAINGROUP","GROUPLOAD");
 for(int i=0 ; i<7 ;i++){
    lv_group_add_obj(group,lv_obj_get_child(mainGroup.strcollbar,i));
 }
 lv_group_set_editing(group,false);//导航模式
 lv_group_focus_obj(mainGroup.strcollbar);
}
//-----------------------------------------------------------------------------
//主界面初始化
void initMainPage(lv_obj_t * page)
{
    ESP_LOGE("MAINPAGE","MAIN");
    //先清理在创建新的组将聚焦聚焦到新的group
    // lv_style_set_bg_color(&Style,lv_color_make(0,0,0));
    //状态栏图标栏
    lv_obj_t * status = mainStatuslindicator(page);
    //中间滚动条
    mainGroup.strcollbar = scrollBarControl(page);
    //时间控件
    clockControl(page);
    //lv_obj_align_to(status,scrollBar->timeControl,LV_ALIGN_OUT_TOP_MID,0,0);
    lv_obj_align_to(status,page,LV_ALIGN_OUT_BOTTOM_MID,0,0);
    //滑动解锁
}







