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
    lv_style_t style;
    bool addImageDisPlay();
    lv_obj_t * scr;
};







