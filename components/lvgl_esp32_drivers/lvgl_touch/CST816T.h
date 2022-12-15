#ifndef CST816T_H
#define CST816T_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

//设备基地址
#define CST816T_I2C_SLAVE_ADDR   0x15
//设备读写基地址
#define CST816T_Write_REG 	    0x2A
#define CST816T_READ_REG 	      0x2B

#define CST816T_IRQ CONFIG_LV_TOUCH_PIN_IRQ
// #define  CST816T_AVG             4
#define CST816T_X_MIN           CONFIG_LV_TOUCH_X_MIN
#define CST816T_Y_MIN           CONFIG_LV_TOUCH_Y_MIN
#define CST816T_X_MAX           CONFIG_LV_TOUCH_X_MAX
#define CST816T_Y_MAX           CONFIG_LV_TOUCH_Y_MAX

/* 触摸屏寄存器 */
#define CST816T_GestureID_REG   0x01
#define CST816T_FingerNum 			0x02
#define CST816T_XposH 				  0x03
#define CST816T_XposL 				0x04
#define CST816T_YposH 				0x05
#define CST816T_YposL 				0x06
#define CST816T_ChipID 				0xA7
#define CST816T_MotionMask 			0xEC
#define CST816T_IrqPluseWidth 		0xED
#define CST816T_NorScanPer 			0xEE
#define CST816T_MotionSlAngle 		0xEF
#define CST816T_LpAutoWakeTime 		0xF4
#define CST816T_LpScanTH 			0xF5
#define CST816T_LpScanWin 			0xF6
#define CST816T_LpScanFreq 			0xF7
#define CST816T_LpScanIdac 			0xF8
#define CST816T_AutoSleepTime 		0xF9
#define CST816T_IrqCtl 				0xFA
#define CST816T_AutoReset 			0xFB
#define CST816T_LongPressTime 		0xFC
#define CST816T_IOCtl 				0xFD
#define CST816T_DisAutoSleep 		0xFE

typedef struct {
    bool inited;
} CST816T_status_t;

typedef struct
{
  int16_t last_x;
  int16_t last_y;
  lv_indev_state_t current_state;
} CST816T_touch_t;

extern CST816T_touch_t CST816_Instance;

typedef enum 
{
  NONE = 0x00, //无手势
  SWIPE_UP = 0x01,//上滑
  SWIPE_DOWN = 0x02,//下滑
  SWIPE_LEFT = 0x03,//左滑
  SWIPE_RIGHT = 0x04,//右滑
  SINGLE_CLICK = 0x05,//单击
  DOUBLE_CLICK = 0x0B,//双击
  LONG_PRESS = 0x0C//长按
} CST816T_Gesture_Id_t;

/* 连续动作配置选项 */
typedef enum
{
	M_DISABLE = 	0x00,
	EnConLR = 		0x01,
	EnConUD = 		0x02,
	EnDClick = 		0x03,
	M_ALLENABLE = 	0x07,
} MotionMask_t;

/* 中断低脉冲发射方式选项 */
typedef enum
{
	OnceWLP = 		0x00,
	EnMotion = 		0x10,
	EnChange = 		0x20,
	EnTouch = 		0x40,
	EnTest = 		0x80,
} IrqCtl_t;

void CST816T_init();
bool CST816T_read(lv_indev_drv_t * drv, lv_indev_data_t * data);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CST816T_H */

