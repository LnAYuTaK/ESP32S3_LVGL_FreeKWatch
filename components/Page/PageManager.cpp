#include "PageManager.h"
PageManager::PageManager()
{
    //src_act 始终位于最底层
    scr = lv_scr_act();
    lv_style_init(&style);
    lv_style_set_radius( &style, 20 );
    lv_style_set_bg_opa( &style, LV_OPA_COVER );
    lv_style_set_bg_color( &style, lv_color_hex(0xff0000) );
    lv_style_set_bg_grad_color( &style, lv_color_hex( 0x0000ff ) );
    lv_style_set_bg_grad_dir( &style, LV_GRAD_DIR_HOR );
    //objectDis = lv_obj_create(scr);
    lv_obj_add_style(scr, &style, LV_PART_MAIN );
}
