/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "rotary_encoder.h"
#define     EC11_A_PIN     39    //编码器通道一
#define     EC11_B_PIN     40    //编码器通道二
#define     EC11_K_PIN     38    //编码器按键通道

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
// static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

// static void mouse_init(void);
// static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
// static bool mouse_is_pressed(void);
// static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y);

// static void keypad_init(void);
// static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
// static uint32_t keypad_get_key(void);
//使用编码器
lv_indev_t * indev_encoder;
static int32_t encoder_diff;
static lv_indev_state_t encoder_state;


static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler();

// static void button_init(void);
// static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
// static int8_t button_get_pressed_id(void);
// static bool button_is_pressed(uint8_t id);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_group_t*  group;
lv_indev_t * indev_touchpad;
// lv_indev_t * indev_mouse;
// lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
// lv_indev_t * indev_button;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;
    static lv_indev_drv_t touchpad_drv;
#if 0
    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    touchpad_init();
    /*Register a touchpad input device*/
    lv_indev_drv_init(&touchpad_drv);
    touchpad_drv.type = LV_INDEV_TYPE_POINTER;
    touchpad_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&touchpad_drv);
#endif
#if 0
    /*------------------
     * Mouse
     * -----------------*/

    /*Initialize your mouse if you have*/
    mouse_init();

    /*Register a mouse input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = mouse_read;
    indev_mouse = lv_indev_drv_register(&indev_drv);

    /*Set cursor. For simplicity set a HOME symbol now.*/
    lv_obj_t * mouse_cursor = lv_img_create(lv_scr_act());
    lv_img_set_src(mouse_cursor, LV_SYMBOL_HOME);
    lv_indev_set_cursor(indev_mouse, mouse_cursor);
#endif
#if 0
    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/
#endif
#if 1
    /*------------------
     * Encoder
     * -----------------*/


//使用编码器
    /*Initialize your encoder if you have*/
    encoder_init();
    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);
    group = lv_group_create();
    lv_indev_set_group(indev_encoder,group);
    lv_group_set_default(group);
    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_encoder, group);`*/
#endif
#if 0
    /*------------------
     * Button
     * -----------------*/

    /*Initialize your button if you have*/
    button_init();

    /*Register a button input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_BUTTON;
    indev_drv.read_cb = button_read;
    indev_button = lv_indev_drv_register(&indev_drv);

    /*Assign buttons to points on the screen*/
    static const lv_point_t btn_points[2] = {
        {10, 10},   /*Button 0 -> x:10; y:10*/
        {40, 100},  /*Button 1 -> x:40; y:100*/
    };
    lv_indev_set_button_points(indev_button, btn_points);
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/

// /*Initialize your touchpad*/
static void touchpad_init(void)
{

touch_driver_init();
    /*Your code comes here*/
}

// /*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    touch_driver_read(indev_drv,data);
}

// /*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    // /*Your code comes here*/
    if(CST816_Instance.current_state != 1) {	
        return true;	
    }
    // /*Your code comes here*/
    return false;
}

// /*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    (*x) = CST816_Instance.last_x;
    (*y) = CST816_Instance.last_y;
}


// /*------------------
//  * Mouse
//  * -----------------*/

// /*Initialize your mouse*/
// static void mouse_init(void)
// {
//     /*Your code comes here*/
// }

// /*Will be called by the library to read the mouse*/
// static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
// {
//     /*Get the current x and y coordinates*/
//     mouse_get_xy(&data->point.x, &data->point.y);

//     /*Get whether the mouse button is pressed or released*/
//     if(mouse_is_pressed()) {
//         data->state = LV_INDEV_STATE_PR;
//     }
//     else {
//         data->state = LV_INDEV_STATE_REL;
//     }
// }

// /*Return true is the mouse button is pressed*/
// static bool mouse_is_pressed(void)
// {
//     /*Your code comes here*/

//     return false;
// }

// /*Get the x and y coordinates if the mouse is pressed*/
// static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y)
// {
//     /*Your code comes here*/

//     (*x) = 0;
//     (*y) = 0;
// }

// /*------------------
//  * Keypad
//  * -----------------*/

// /*Initialize your keypad*/
// static void keypad_init(void)
// {
//     /*Your code comes here*/
// }

// /*Will be called by the library to read the mouse*/
// static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
// {
//     static uint32_t last_key = 0;

//     /*Get the current x and y coordinates*/
//     mouse_get_xy(&data->point.x, &data->point.y);

//     /*Get whether the a key is pressed and save the pressed key*/
//     uint32_t act_key = keypad_get_key();
//     if(act_key != 0) {
//         data->state = LV_INDEV_STATE_PR;

//         /*Translate the keys to LVGL control characters according to your key definitions*/
//         switch(act_key) {
//             case 1:
//                 act_key = LV_KEY_NEXT;
//                 break;
//             case 2:
//                 act_key = LV_KEY_PREV;
//                 break;
//             case 3:
//                 act_key = LV_KEY_LEFT;
//                 break;
//             case 4:
//                 act_key = LV_KEY_RIGHT;
//                 break;
//             case 5:
//                 act_key = LV_KEY_ENTER;
//                 break;
//         }

//         last_key = act_key;
//     }
//     else {
//         data->state = LV_INDEV_STATE_REL;
//     }

//     data->key = last_key;
// }

// /*Get the currently being pressed key.  0 if no key is pressed*/
// static uint32_t keypad_get_key(void)
// {
//   return 0;
// }

/*------------------
 * Encoder
 * -----------------*/
/*Initialize your keypad*/
rotary_encoder_t *encoder = NULL;
static int countLast = 0;
uint32_t pcnt_unit = 0;
static void encoder_init(void)
{
    rotary_encoder_config_t config = ROTARY_ENCODER_DEFAULT_CONFIG((rotary_encoder_dev_t)pcnt_unit, 39, 40);
    ESP_ERROR_CHECK(rotary_encoder_new_ec11(&config, &encoder));

    // Filter out glitch (1us)
    ESP_ERROR_CHECK(encoder->set_glitch_filter(encoder, 1));

    // Start encoder
    ESP_ERROR_CHECK(encoder->start(encoder));

}

static void 
encoder_handler()
{
    /*Your code comes here*/
    static bool but_flag = true;
    int nowCount = encoder->get_counter_value(encoder)/4.0;
    
    if(countLast > nowCount&&but_flag){
        encoder_diff = 1;
        but_flag = false;
    }else if(countLast < nowCount&&but_flag){
        encoder_diff = -1;
        but_flag = false;
    }else{
        encoder_diff = 0;
        but_flag = true;
    }
    countLast = nowCount;
    // printf("%d  %d\n",nowCount,encoder_diff);
    if(gpio_get_level(EC11_K_PIN)==0)
        encoder_state = LV_INDEV_STATE_PR;
    else
        encoder_state = LV_INDEV_STATE_REL;
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    encoder_handler();
    data->enc_diff = encoder_diff;
    data->state = encoder_state;
    encoder_diff = 0;
}


// /*------------------
//  * Button
//  * -----------------*/

// /*Initialize your buttons*/
// static void button_init(void)
// {
//     /*Your code comes here*/ 
// }

// /*Will be called by the library to read the button*/
// static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
// {

//     static uint8_t last_btn = 0;

//     /*Get the pressed button's ID*/
//     int8_t btn_act = button_get_pressed_id();

//     if(btn_act >= 0) {
//         data->state = LV_INDEV_STATE_PR;
//         last_btn = btn_act;
//     }
//     else {
//         data->state = LV_INDEV_STATE_REL;
//     }

//     /*Save the last pressed button's ID*/
//     data->btn_id = last_btn;
// }

// /*Get ID  (0, 1, 2 ..) of the pressed button*/
// static int8_t button_get_pressed_id(void)
// {
//     uint8_t i;

//     /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
//     for(i = 0; i < 2; i++) {
//         /*Return the pressed button's ID*/
//         if(button_is_pressed(i)) {
//             return i;
//         }
//     }

//     /*No button pressed*/
//     return -1;
// }

// /*Test if `id` button is pressed or not*/
// static bool button_is_pressed(uint8_t id)
// {

//     /*Your code comes here*/

//     return false;
// }

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
