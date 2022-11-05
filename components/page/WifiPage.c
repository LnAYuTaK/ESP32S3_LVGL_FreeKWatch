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
static void 
wifiListViewBtnCb(lv_event_t e)
{

}

//wifi列表组件
lv_obj_t *
wifiListViewCreate(lv_obj_t * page)
{
    static lv_style_t  listViewStyle;
    lv_style_reset(&listViewStyle);
    lv_style_init(&listViewStyle);
    lv_style_set_pad_all(&listViewStyle,0);
    lv_obj_t * listView = lv_list_create(page);
    lv_obj_set_style_pad_column(listView,20, LV_PART_MAIN);  
    lv_style_set_bg_color(&listViewStyle,lv_color_make(155,160,170));
    lv_obj_add_style(listView,&listViewStyle,0);
    uint16_t num;
    wifi_ap_record_t records[8];
    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_num(&num);
    if(num > 8){
        num = 8;	
    }
    esp_wifi_scan_get_ap_records(&num, records);
    if(num > 8){
        num = 8;	
    }
    for(int i = 0; i < num; i++) {
    //     uint8_t rssi_level = 0;
    //     switch (records[i].rssi) {
    //         case -100 ... -88:
    //             rssi_level = 1; break;
    //         case -87 ... -77:
    //             rssi_level = 2; break;
    //         case -76 ... -66:
    //             rssi_level = 3; break;
    //         case -65 ... -55:
    //             rssi_level = 4; break;
    //         default:
    //             if(records[i].rssi < -100){
    //                 rssi_level = 0;
    //             }else{
    //                 rssi_level = 5;
    //             }
    //             break;
    // }
	lv_obj_t * btn = lv_list_add_btn(listView,LV_SYMBOL_WIFI,(char*)records[i].ssid);
    lv_obj_add_event_cb(btn, wifiListViewBtnCb, LV_EVENT_CLICKED,(char*)records[i].ssid);  
    }
    wifiGroup.listView =  listView;
    return listView;
}
//返回上一步
static void lv_page_back_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_100ask_page_manager_t * page_manager =  (lv_100ask_page_manager_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
        lv_ll_t * history_ll = &(page_manager->history_ll);
        /* The current page */
        lv_100ask_page_manager_history_t * act_hist = _lv_ll_get_head(history_ll);
        /* The previous page */
        lv_100ask_page_manager_history_t * prev_hist = _lv_ll_get_next(history_ll, act_hist);
        if(prev_hist != NULL) {
            lv_100ask_page_manager_set_close_page(act_hist->page, NULL);
            /* Previous page exists */
            /* Delete the current item from the history */
            _lv_ll_remove(history_ll, act_hist);
            lv_mem_free(act_hist);
            page_manager->cur_depth--;
            /* Create the previous page.
            *  Remove it from the history because `lv_100ask_page_manager_set_open_page` will add it again */
            _lv_ll_remove(history_ll, prev_hist);
            page_manager->cur_depth--;
            lv_100ask_page_manager_set_open_page(prev_hist->page, NULL);
            lv_mem_free(prev_hist);
        }
    }
}

void wifiGroupLoad(lv_obj_t * scr)
{ 
    lv_group_add_obj(group,wifiGroup.backbtn);
    //WifiList
    for(int i=0 ;i < 8 ;i++) {
        lv_obj_t * obj = lv_obj_get_child(wifiGroup.listView,i);
        if(obj!=NULL) {
            lv_group_add_obj(group,obj);
        }
    }
    lv_group_set_editing(group,false);//导航模式
    lv_group_focus_obj(scr);
}
//-----------------------------------------------------------------------------
void initWifiPage(lv_obj_t * page)
{ 

    lv_obj_set_style_bg_color(page,lv_color_black(),0);
    lv_obj_set_style_bg_opa(page,LV_OPA_COVER,0);
    header_t * header  = headerCreate(page,"WIFI");
    wifiGroup.backbtn = header->backBtnH;
    lv_obj_add_event_cb(header->backBtnH, lv_page_back_event_cb, LV_EVENT_CLICKED, lv_obj_get_parent(page));  
    lv_obj_add_flag(header->backBtnH, LV_OBJ_FLAG_CLICKABLE);
    static lv_style_t rootStyle;
    lv_style_reset(&rootStyle);
    lv_style_init(&rootStyle);
    lv_obj_t * root = lv_obj_create(page);
    lv_obj_align_to(root,header->mainHeaderH,LV_ALIGN_OUT_BOTTOM_MID,-75,0);
    lv_obj_add_style(root,&rootStyle,0);
    lv_obj_set_size(root,LV_PCT(100),LV_PCT(100));
    //创建wifi列表
    lv_obj_t *listView = wifiListViewCreate(root);
    lv_obj_set_size(listView,LV_PCT(100),LV_PCT(100));
    //
}
//-----------------------------------------------------------------------------


