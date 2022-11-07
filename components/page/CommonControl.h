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
    lv_obj_t * mainMenu;
}Menu_t;

/**********************
 *      FUNCTION
 **********************/
lv_obj_t * menuCreate(lv_obj_t * obj,const char *pageName);

lv_obj_t* createText(lv_obj_t* parent, const char* icon, const char* txt);
#endif //COMMONCONTROL_H







