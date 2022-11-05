#include "CommonControl.h"
#include "backIcon.c"
LV_IMG_DECLARE(backIcon);
//标题栏组件//
header_t * headerCreate(lv_obj_t * page,const char *pageName)
{
    //标题栏
    static header_t headerControl = {0};
    static lv_style_t headerStyle;
    lv_style_reset(&headerStyle);
    lv_style_init(&headerStyle);
    lv_obj_t * header = lv_obj_create(page);
    lv_obj_set_style_bg_opa(header, LV_OPA_0, 0);
    lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(header, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(header,LV_PCT(100),60);
    lv_obj_add_style(header,&headerStyle,0);
    //标题按键返回
    static lv_style_t btnStyle;
    lv_style_reset(&btnStyle);
    lv_style_init(&btnStyle);
    lv_style_set_bg_opa(&btnStyle,LV_OPA_0);
    lv_style_set_bg_img_src(&btnStyle,&backIcon);
    lv_style_set_bg_img_opa(&btnStyle,LV_OPA_COVER);
    lv_obj_t * backBtn = lv_btn_create(header);
    lv_obj_set_size(backBtn,LV_PCT(100),32);
    lv_obj_align(backBtn,LV_ALIGN_BOTTOM_LEFT,-20,0);

    lv_obj_add_style(&btnStyle, &btnStyle,0);
    //标题描述
    static lv_style_t textStyle;
    lv_style_reset(&textStyle);
    lv_style_init(&textStyle);
    lv_style_set_text_color(&textStyle,lv_color_white());
    lv_obj_t * pageDesLab= lv_label_create(header);
    lv_obj_set_size(pageDesLab,LV_PCT(100),32);
    lv_label_set_text(pageDesLab,pageName);
    lv_obj_align_to(pageDesLab,backBtn,LV_ALIGN_OUT_RIGHT_BOTTOM,0,0);
    lv_obj_add_style(pageDesLab,&textStyle,0);
    headerControl.backBtnH = backBtn;
    headerControl.pageDesLabH = pageDesLab;
    headerControl.mainHeaderH = header;
    return &headerControl;
}
