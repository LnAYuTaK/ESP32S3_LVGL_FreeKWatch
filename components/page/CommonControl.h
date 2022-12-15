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

// lv_obj_t* menuDesCreate(lv_obj_t* parent, const char* icon, const char* txt ,const char * des);

lv_obj_t* menuTextCreate(lv_obj_t* parent, const char* icon, const char* txt);

lv_obj_t *menuSectionCreate(lv_obj_t* page,const char * icon,const char * titile);
#endif //COMMONCONTROL_H







