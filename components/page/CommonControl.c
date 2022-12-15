#include "CommonControl.h"
#include "backIcon.c"
LV_IMG_DECLARE(backIcon);

// MenuPage  
//-----------------------------------------------------------------------------
// lv_obj_t*   //图标 功能 描述
// menuDesCreate(lv_obj_t* parent, const char* icon, const char* txt)
// {
//     lv_obj_t* obj = lv_menu_cont_create(parent);
//     lv_obj_t* label = NULL;
//     lv_obj_t * img  = NULL;

//     if(icon) {
//         img = lv_img_create(obj);
//         lv_img_set_src(img, icon);
//     }

//     if (txt) {
//         label = lv_label_create(obj);
//         lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
//     }
//     return obj;
// }
//-----------------------------------------------------------------------------
lv_obj_t* 
menuTextCreate(lv_obj_t* parent, const char* icon, const char* txt)
{
    lv_obj_t* obj = lv_menu_cont_create(parent);
    lv_obj_t* img = NULL;
    lv_obj_t* label = NULL;
    if (icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }
    if (txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }
    return obj;
}
//-----------------------------------------------------------------------------
lv_obj_t *
menuSectionCreate(lv_obj_t* page,const char * icon,const char * titile)
{
    lv_obj_t* img = NULL;
    if (icon) {
        img = lv_img_create(page);
        lv_img_set_src(img, icon);
    }
    static lv_style_t  sectionStyle;
    lv_style_reset(&sectionStyle);
    lv_style_init(&sectionStyle);
    lv_style_set_radius(&sectionStyle,20);
    lv_obj_t* section = lv_menu_section_create(page);
    lv_obj_set_style_bg_color(section,lv_color_make(77,77,77),0);
    lv_obj_set_size(section,LV_PCT(80),70);
    lv_obj_add_style(section,&sectionStyle,0);
    return  section;
}
//返回键的回调
//-----------------------------------------------------------------------------
static 
void lv_page_back_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_UNUSED(obj);
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
            _lv_ll_remove(history_ll, act_hist);
            lv_mem_free(act_hist);
            page_manager->cur_depth--;
            _lv_ll_remove(history_ll, prev_hist);
            page_manager->cur_depth--;
            lv_100ask_page_manager_set_open_page(prev_hist->page, NULL);
            lv_mem_free(prev_hist);
        }
    }
}
//-----------------------------------------------------------------------------
//统一外部菜单 
lv_obj_t * 
menuCreate(lv_obj_t * page,const char *pageName)
{
    //初始化初始化菜单
    static lv_style_t menuStyle;
    lv_style_reset(&menuStyle);
    lv_style_init(&menuStyle);
    lv_obj_t * menu = lv_menu_create(page);
    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));
    lv_obj_center(menu);
    lv_obj_add_event_cb(lv_menu_get_main_header_back_btn(menu), lv_page_back_event_cb, LV_EVENT_CLICKED, lv_obj_get_parent(page));  
    lv_obj_add_flag(lv_menu_get_main_header_back_btn(menu), LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_style(menu,&menuStyle,0);
    static lv_style_t rootPageStyle;
    lv_style_reset(&rootPageStyle);
    lv_style_init(&rootPageStyle);
    lv_obj_t * rootPage = lv_menu_page_create(menu ,(char *)pageName); 
    lv_style_set_flex_flow(&rootPageStyle,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(rootPage,10, 0); 
    lv_obj_add_style(rootPage,&rootPageStyle,0);
    lv_menu_set_page(menu, rootPage);
    return  menu;
}








