#ifndef WIFIPAGE_H
#define WIFIPAGE_H
#include "MainPage.h"
extern void initWifiPage(lv_obj_t * page);

extern void wifiGroupLoad(lv_obj_t * scr);
//WIFI group struct 
//wifi列表
typedef struct wifiView
{
  lv_obj_t *wifiView
}wifiView_t;

typedef struct wifiGroup
{
  //退出按键//
  lv_obj_t *backbtn;
  lv_obj_t *listView;
    /* data */
}wifiGroup_t;

#endif //WIFIPAFE_H