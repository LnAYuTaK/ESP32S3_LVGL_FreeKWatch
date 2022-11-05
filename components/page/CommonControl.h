#ifndef COMMONCONTROL_H
#define COMMONCONTROL_H
/*********************
 *      INCLUDES
*********************/
#include "MainPage.h"
#include "lv_port_indev.h"
/*********************
 *      BGIMG
*********************/


/*********************
 *      DEFINES
 *********************/
typedef struct {
    lv_obj_t * mainHeaderH;
    lv_obj_t * backBtnH;
    lv_obj_t * pageDesLabH
}header_t;

/**********************
 *      FUNCTION
 **********************/
header_t * headerCreate(lv_obj_t * obj,const char *pageName);
#endif //COMMONCONTROL_H







