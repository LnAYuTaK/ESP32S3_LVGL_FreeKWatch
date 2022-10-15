#pragma once 
#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"
#ifdef __cplusplus
} 
#endif
class PageManager
{
private:
    /* data */
public:
    PageManager(/* args */);
    lv_obj_t * scr =nullptr;
    lv_obj_t * objectDis =nullptr;
    lv_style_t style;
};






