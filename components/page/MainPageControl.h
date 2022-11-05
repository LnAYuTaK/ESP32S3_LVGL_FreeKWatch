#ifndef MAINPAGECONTROL_H
#define MAINPAGECONTROL_H
/*********************
 *      INCLUDES
*********************/
#include "MainPage.h"
/*********************
 *      TYPEDEFINES
 *********************/

//时钟控件结构体
typedef struct _lv_clock
{
    lv_obj_t *timeLabel; // 时间标签
    lv_obj_t *dateLabel; // 日期标签
    lv_obj_t *timeControl; // 星期标签
}clockPointer;

//时钟控件结构体


/**********************
 *      FUNCTION
 **********************/
//滚动条初始化 
lv_obj_t * scrollBarControl(lv_obj_t * page);
//创建时间结构体
clockPointer *clockControl(lv_obj_t * page);
//主状态显示器
lv_obj_t *mainStatuslindicator(lv_obj_t *page);
#endif //MAINPAGECONTROL_H