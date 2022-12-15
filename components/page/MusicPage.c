
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
    return cont;
}
//-----------------------------------------------------------------------------
void 
initMusicPage(lv_obj_t * page)
{






}