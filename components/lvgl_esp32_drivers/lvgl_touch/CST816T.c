#include <esp_log.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif
#include "CST816T.h"
#include "lvgl_i2c/i2c_manager.h"
#define TAG "CST816T"

CST816T_status_t CST816T_status;
static uint8_t current_dev_addr; 
CST816T_touch_t CST816_Instance;

//i2c 读8bit
static esp_err_t CST816T_i2c_read8(uint8_t slave_addr, uint8_t register_addr, uint8_t *data_buf) {
    return lvgl_i2c_read(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr, data_buf, 1);
}
//i2c 写8bit
static esp_err_t CST816T_i2c_write8(uint8_t slave_addr, uint8_t register_addr, uint8_t *data_buf) {
    return lvgl_i2c_write(CONFIG_LV_I2C_TOUCH_PORT, slave_addr, register_addr, data_buf, 1);
}

void CST816T_init()
{
    CST816T_status.inited = true;
    // uint8_t data_buf;
}

bool CST816T_read(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    // static lv_coord_t last_x = 0;
    // static lv_coord_t last_y = 0;
    if (!CST816T_status.inited) {
        ESP_LOGE(TAG, "Init first!");
        return 0x00;
    }
    uint8_t data_buf[4];
    uint8_t penflag;     
    esp_err_t ret =  CST816T_i2c_read8(CST816T_I2C_SLAVE_ADDR,CST816T_FingerNum,&penflag);
    //
    CST816T_i2c_read8(CST816T_I2C_SLAVE_ADDR,CST816T_XposH,data_buf);
    if (ret != ESP_OK) {    // ignore no touch & multi touch
        if ( CST816_Instance.current_state != LV_INDEV_STATE_REL)
        {
            CST816_Instance.current_state = LV_INDEV_STATE_REL;
        } 
        data->point.x = CST816_Instance.last_x;
        data->point.y = CST816_Instance.last_y;
        data->state =CST816_Instance.current_state;
        return false;
    }
    CST816_Instance.current_state = LV_INDEV_STATE_PR;
    CST816_Instance.last_x = ((data_buf[0]&0x0F)<<8 | data_buf[1]);
    CST816_Instance.last_y = ((data_buf[2]&0x0F)<<8 | data_buf[3]);
    data->point.x = CST816_Instance.last_x;
    data->point.y = CST816_Instance.last_y;
    data->state   = CST816_Instance.current_state;
    ESP_LOGD(TAG, "X=%u Y=%u", data->point.x, data->point.y);

#if CONFIG_LV_FT6X36_COORDINATES_QUEUE
    xQueueOverwrite( ft6x36_touch_queue_handle, &touch_inputs );
#endif
    return false;
}





