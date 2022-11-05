
#include "MusicPage.h"
#include "play.c"
#include "shangyishou.c"
#include "suijisenlin.c"
#include "xiayishou.c"
#include "xunhuan.c"
#include "zanting.c"
#include "MainPage.h"
#include "esp_log.h"
LV_IMG_DECLARE(xunhuan);
LV_IMG_DECLARE(suijisenlin);
LV_IMG_DECLARE(shangyishou);
LV_IMG_DECLARE(xiayishou);
LV_IMG_DECLARE(play);
LV_IMG_DECLARE(zanting);

static const char* TAG = "MusicPage";
//-----------------------------------------------------------------------------
lv_obj_t *
create_ctrl_box(lv_obj_t * page)
{
    ESP_LOGI(TAG,"DEBUG_Create_Ctr");
    lv_obj_t * cont = lv_obj_create(page);
    lv_obj_center(cont);
    lv_obj_remove_style_all(cont);
    lv_obj_set_height(cont, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_bottom(cont, 8, 0);
    static const lv_coord_t grid_col[] = {LV_GRID_FR(2), LV_GRID_FR(3), LV_GRID_FR(5), LV_GRID_FR(5), LV_GRID_FR(5), LV_GRID_FR(3), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};
    static const lv_coord_t grid_row[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(cont, grid_col, grid_row);

    lv_obj_t * icon= lv_img_create(cont);
    lv_img_set_src(icon, &suijisenlin);
    lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    icon = lv_img_create(cont);
    lv_img_set_src(icon, &xunhuan);
    lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_END, 5, 1, LV_GRID_ALIGN_CENTER, 0, 1);

//     icon = lv_img_create(cont);
//     lv_img_set_src(icon, &shangyishou);
//     lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_CENTER, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);
//     // lv_obj_add_event_cb(icon, prev_click_event_cb, LV_EVENT_CLICKED, NULL);

//     lv_obj_t * play_obj = lv_imgbtn_create(cont);
//     lv_imgbtn_set_src(play_obj, LV_IMGBTN_STATE_RELEASED, NULL, &play, NULL);
//     lv_imgbtn_set_src(play_obj, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &zanting, NULL);
//     lv_obj_add_flag(play_obj, LV_OBJ_FLAG_CHECKABLE);
//     lv_obj_set_grid_cell(play_obj, LV_GRID_ALIGN_CENTER, 3, 1, LV_GRID_ALIGN_CENTER, 0, 1);

//     // lv_obj_add_event_cb(play_obj, play_event_click_cb, LV_EVENT_CLICKED, NULL);
//     lv_obj_add_flag(play_obj, LV_OBJ_FLAG_CLICKABLE);
//     lv_obj_set_width(play_obj, play.header.w);

//     icon = lv_img_create(cont);
//     lv_img_set_src(icon, &xiayishou);
//     lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_CENTER, 4, 1, LV_GRID_ALIGN_CENTER, 0, 1);
//    // lv_obj_add_event_cb(icon, next_click_event_cb, LV_EVENT_CLICKED, NULL);
//     lv_obj_add_flag(icon, LV_OBJ_FLAG_CLICKABLE);

    // LV_IMG_DECLARE(img_lv_demo_music_slider_knob);
    // slider_obj = lv_slider_create(cont);
    // lv_obj_set_style_anim_time(slider_obj, 100, 0);
    // lv_obj_add_flag(slider_obj, LV_OBJ_FLAG_CLICKABLE); /*No input from the slider*/

    //lv_obj_set_grid_cell(slider_obj, LV_GRID_ALIGN_STRETCH, 1, 4, LV_GRID_ALIGN_CENTER, 1, 1);

    // lv_obj_set_style_bg_img_src(slider_obj, &img_lv_demo_music_slider_knob, LV_PART_KNOB);
    // lv_obj_set_style_bg_opa(slider_obj, LV_OPA_TRANSP, LV_PART_KNOB);
    // lv_obj_set_style_pad_all(slider_obj, 20, LV_PART_KNOB);
    // lv_obj_set_style_bg_grad_dir(slider_obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR);
    // lv_obj_set_style_bg_color(slider_obj, lv_color_hex(0x569af8), LV_PART_INDICATOR);
    // lv_obj_set_style_bg_grad_color(slider_obj, lv_color_hex(0xa666f1), LV_PART_INDICATOR);
    // lv_obj_set_style_outline_width(slider_obj, 0, 0);

    // time_obj = lv_label_create(cont);
    // lv_obj_set_style_text_font(time_obj, font_small, 0);
    // lv_obj_set_style_text_color(time_obj, lv_color_hex(0x8a86b8), 0);
    // lv_label_set_text(time_obj, "0:00");
    // lv_obj_set_grid_cell(time_obj, LV_GRID_ALIGN_END, 5, 1, LV_GRID_ALIGN_CENTER, 1, 1);
    return cont;
}
//-----------------------------------------------------------------------------
void initMusicPage(lv_obj_t * page)
{
//Music界面初始化
//    create_ctrl_box(page);
//  lv_obj_set_size(cont,150,60);
}