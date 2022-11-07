#include "WifiPage.h"
#include <stdio.h>
#include <string.h>
#include "wifi.h"
#include  "esp_log.h"
//INPUT
#include "lv_port_indev.h"
#include "CommonControl.h"
//Singleton var
static wifiGroup_t wifiGroup;
// //
//-----------------------------------------------------------------------------
static void 
wifiListViewBtnCb(lv_event_t e)
{

    //MESSAGEBOX()

}
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
    // wifiGroup.listView =  listView;
    return listView;
}
//-----------------------------------------------------------------------------
void wifiGroupLoad(lv_obj_t * scr)
{ 
    lv_group_add_obj(group,wifiGroup.backbtn);
    //WifiList
    // for(int i=0 ;i < 8 ;i++) {
    //     lv_obj_t * obj = lv_obj_get_child(wifiGroup.listView,i);
    //     if(obj!=NULL) {
    //         lv_group_add_obj(group,obj);
    //     }
    // }
    lv_group_set_editing(group,false);//导航模式
    lv_group_focus_obj(scr);
}
//-----------------------------------------------------------------------------
void
setWifiGroup(lv_obj_t * menu)
{
    //按键//
    wifiGroup.backbtn  =lv_menu_get_main_header_back_btn(menu);
}
//-----------------------------------------------------------------------------
void 
initWifiPage(lv_obj_t * page)
{ 
    lv_obj_t  * wifiMenu  = menuCreate(page,"WIFI");
    setWifiGroup(wifiMenu);
    lv_obj_t *rootPage = lv_menu_get_cur_main_page(wifiMenu);
    //wifiConfig
    createText(rootPage, NULL, "WLAN"); 

    lv_obj_t * wifiConfig = lv_menu_section_create(rootPage);

    static lv_style_t countStyle;
    lv_style_reset(&countStyle);
    lv_style_init(&countStyle);
    lv_obj_set_style_bg_color(wifiConfig,lv_palette_main(LV_PALETTE_GREY),0);
    lv_obj_add_style(wifiConfig,&countStyle,0);

    createText(wifiConfig,NULL,"WIFI"); 
    createText(wifiConfig,NULL,"Settings");  
    //Connected wlan
    createText(rootPage,NULL, "Connected wlan"); 
    lv_obj_t * wifiConnect = lv_menu_section_create(rootPage);
    //Available wlan
    createText(rootPage, NULL, "Available wlan"); 
    lv_obj_t * wifiAvailable = lv_menu_section_create(rootPage);
    //ListView
    // wifiListViewCreate(wifiAvailable);
}
//-----------------------------------------------------------------------------


