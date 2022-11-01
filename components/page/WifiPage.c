#include "WifiPage.h"
void initWifiPage(lv_obj_t * page)
{
    //WIFI界面初始化
    static lv_style_t Style;
    lv_style_init(&Style);
    lv_obj_set_style_bg_color(page,lv_color_black(), LV_PART_MAIN);
    lv_obj_add_style(page, &Style, 0);
}