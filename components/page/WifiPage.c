#include "WifiPage.h"
#include <stdio.h>
#include <string.h>
#include "wifi.h"
#include  "esp_log.h"
//INPUT
#include "lv_port_indev.h"
#include "CommonControl.h"
//Singleton var
//-----------------------------------------------------------------------------
//wifi列表组件
lv_obj_t *
wifiListViewCreate(lv_obj_t * page)
{
    static lv_style_t  listViewStyle;
    lv_style_reset(&listViewStyle);
    lv_style_init(&listViewStyle);
    lv_style_set_pad_all(&listViewStyle,0);
    lv_obj_t * listView = lv_list_create(lv_menu_cont_create(page));
    lv_obj_set_style_pad_column(listView,5, LV_PART_MAIN);  
    lv_style_set_bg_color(&listViewStyle,lv_color_make(155,160,170));
    lv_obj_add_style(listView,&listViewStyle,0);
    lv_obj_set_size(listView,LV_PCT(100),LV_PCT(100));
    uint16_t num;
    wifi_ap_record_t records[8];
    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_num(&num);
    if(num > 5){
        num = 5;	
    }
    esp_wifi_scan_get_ap_records(&num, records);
    if(num > 5){
        num = 5;	
    }
    for(int i = 0; i < num; i++) {
	lv_obj_t * btn = lv_list_add_btn(listView,LV_SYMBOL_WIFI,(char*)records[i].ssid);
    }
    return listView;
}
//-----------------------------------------------------------------------------
//WIFI Sub Page
void  //WIFI 
initWifiSettingPage(lv_obj_t * page)
{






}
//-----------------------------------------------------------------------------

void  //WIFI 
initWifiPage(lv_obj_t * page)
{ 
    //wifi  //
    //Back  //title
    //Connect  Page 
    //Setting  Page
    lv_obj_t  * wifiMenu  = menuCreate(page,"WifiConnect");
    lv_obj_t * rootPage = lv_menu_get_cur_main_page(wifiMenu);

    //
    lv_obj_t wifiSettingPage = lv_100ask_page_manager_page_create(wifiMenu, "Main_page");
    lv_100ask_page_manager_set_page_init(wifiMenu,initWifiSettingPage);

    lv_obj_t * wifiSetting = menuSectionCreate(rootPage,NULL,"Connect");
    lv_obj_t * wifiSetting = menuSectionCreate(rootPage,NULL,"Setting");

}
//-----------------------------------------------------------------------------
