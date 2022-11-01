#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "PageManager.h"
//FUNCTION
/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/


/***********************
 * GLOBAL VARIABLES
 ***********************/
extern lv_obj_t  *  page_manager;
extern lv_obj_t  *  main_page;
extern lv_obj_t  *  wifiPage; 
extern lv_group_t*  group;
/**********************
 * GLOBAL PROTOTYPES
 **********************/
void PageInit();
static void button_event_cb(lv_event_t* event);
static void initMainPage(lv_obj_t * page);
// static void open_page_anim(lv_obj_t * obj);
// static void close_page_anim(lv_obj_t * obj);
/*=====================
 * Setter functions
 *====================*/


/*=====================
 * Getter functions
 *====================*/

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/


#endif /*LV_100ASK_PAGE_MANAGER_SIMPLE_TEST*/