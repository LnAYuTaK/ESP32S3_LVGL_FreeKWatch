//消息提示提示窗口(模态)
#include "AppConfig.h"
#include "CommonControl.h"
static void msgbox_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * msgbox = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        const char * txt = lv_msgbox_get_active_btn_text(msgbox);
        if(txt) {
            lv_msgbox_close(msgbox);
        }
    }
}

lv_obj_t * msgbox_create(const char * title ,const char *des)
{
    static const char * btns[] = {"Ok", "Cancel", ""};
    lv_obj_t * mbox = lv_msgbox_create(NULL, title, des, btns, false);
    lv_obj_add_event_cb(mbox, msgbox_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_state(lv_msgbox_get_btns(mbox), LV_STATE_FOCUS_KEY);
    lv_obj_align(mbox, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t * bg = lv_obj_get_parent(mbox);
    lv_obj_set_style_bg_opa(bg, LV_OPA_70, 0);
    lv_obj_set_style_bg_color(bg,lv_color_make,0);
    lv_obj_set_style_border_width(bg,2,0);
    lv_obj_set_style_border_color(bg,SectionColor,0);
    return mbox;
}





