#include "MainPageControl.h"
#include "time.h"
//ICON
#include "aiImg.c"
#include "linggan.c"
#include "yinle.c"
#include "shipin.c"
#include "weixin.c"
#include "wenjian.c"
#include "wifiicon.c"
#include "wifistateOn.c"
#include "dianliang.c"
//INPUT
#include "lv_port_indev.h"
LV_IMG_DECLARE(yinle);//红色
LV_IMG_DECLARE(linggan);//橙色
LV_IMG_DECLARE(shipin_);//黄色
LV_IMG_DECLARE(weixin);//绿色
LV_IMG_DECLARE(wenjian);//青色
LV_IMG_DECLARE(wifiicon);//蓝色
LV_IMG_DECLARE(aiImg);//紫色
LV_IMG_DECLARE(dianliang)//电量图标
LV_IMG_DECLARE(wifistateOn)//wifi状态
//-----------------------------------------------------------------------------
lv_obj_t * 
scrollBarControl(lv_obj_t * page)
{
//初始化中间滚动条按键  
    lv_obj_t * container = lv_obj_create(page);
    lv_obj_set_size(container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
    lv_obj_add_flag(container,LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scroll_snap_x(container, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_style_bg_opa(container, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 3, LV_PART_MAIN);
    lv_obj_set_style_border_color(container ,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_pad_column(container,10, LV_PART_MAIN); 
//音乐
    lv_obj_t* yinleBtn = lv_btn_create(container);
    lv_obj_set_size(yinleBtn, 70, 70);
    static lv_style_t yinleBtnStyle;
    lv_style_reset(&yinleBtnStyle);
    lv_style_init(&yinleBtnStyle);
    lv_obj_set_style_bg_img_src(yinleBtn,&yinle,0);
    lv_obj_set_style_bg_opa(yinleBtn,LV_OPA_0,0);
    lv_obj_add_style(yinleBtn,&yinleBtnStyle,0);
    lv_100ask_page_manager_set_load_page_event (yinleBtn,NULL,"Music_page"); 
//灵感
    lv_obj_t* lingGanBtn = lv_btn_create(container);
    lv_obj_set_size(lingGanBtn, 70, 70);
    static lv_style_t lingGanBtnStyle;
    lv_style_reset(&lingGanBtnStyle);
    lv_style_init(&lingGanBtnStyle);
    lv_obj_set_style_bg_img_src(lingGanBtn,&linggan,0);
    lv_obj_set_style_bg_opa(lingGanBtn,LV_OPA_0,0);
    lv_obj_add_style(lingGanBtn,&lingGanBtnStyle,0);
//视频
    lv_obj_t* shiPinBtn = lv_btn_create(container);
    lv_obj_set_size(shiPinBtn, 70, 70);
    static lv_style_t shiPinBtnStyle;
    lv_style_reset(&shiPinBtnStyle);
    lv_style_init(&shiPinBtnStyle);
    lv_obj_set_style_bg_img_src(shiPinBtn,&shipin_,0);
    lv_obj_set_style_bg_opa(shiPinBtn,LV_OPA_0,0);
    lv_obj_add_style(shiPinBtn,&shiPinBtnStyle,0);
//微信
    lv_obj_t* weiXinBtn = lv_btn_create(container);
    lv_obj_set_size(weiXinBtn, 70, 70);
    static lv_style_t  weiXinBtnStyle;
    lv_style_reset(&weiXinBtnStyle);
    lv_style_init(& weiXinBtnStyle);
    lv_obj_set_style_bg_img_src(weiXinBtn,&weixin,0);
    lv_obj_set_style_bg_opa( weiXinBtn,LV_OPA_0,0);
    lv_obj_add_style(weiXinBtn,& weiXinBtnStyle,0);
//文件    
    lv_obj_t* wenJianBtn = lv_btn_create(container);
    lv_obj_set_size(wenJianBtn, 70, 70);
    static lv_style_t  wenJianBtnStyle;
    lv_style_reset(&wenJianBtnStyle);
    lv_style_init(& wenJianBtnStyle);
    lv_obj_set_style_bg_img_src( wenJianBtn,&wenjian,0);
    lv_obj_set_style_bg_opa( wenJianBtn,LV_OPA_0,0);
    lv_obj_add_style(wenJianBtn,& wenJianBtnStyle,0);
//wifi
    lv_obj_t* wifiBtn = lv_btn_create(container);
    lv_obj_set_size(wifiBtn, 70, 70);
    static lv_style_t  wifiBtnStyle;
    lv_style_reset(&wifiBtnStyle);
    lv_style_init(&wifiBtnStyle);
    lv_obj_set_style_bg_img_src( wifiBtn,&wifiicon,0);
    lv_obj_set_style_bg_opa(wifiBtn,LV_OPA_0,0);
    lv_obj_add_style(wifiBtn,& wifiBtnStyle,0);
    //wifi页面回调
    lv_100ask_page_manager_set_load_page_event(wifiBtn,NULL,"Wifi_page");
//AI
    lv_obj_t* aiImgBtn = lv_btn_create(container);
    lv_obj_set_size(aiImgBtn, 70, 70);
    static lv_style_t  aiImgBtnStyle;
    lv_style_reset(&aiImgBtnStyle);
    lv_style_init(& aiImgBtnStyle);
    lv_obj_set_style_bg_img_src(aiImgBtn,&aiImg,0);
    lv_obj_set_style_bg_opa(aiImgBtn,LV_OPA_0,0);
    lv_obj_add_style(aiImgBtn,& aiImgBtnStyle,0);
    uint32_t mid_btn_index = (lv_obj_get_child_cnt(container) - 1) / 2;
    for (uint32_t i = 0; i < mid_btn_index; i++)
    {
        lv_obj_move_to_index(lv_obj_get_child(container, -1), 0);
    }
    /*当按钮数为偶数时，确保按钮居中*/
    lv_obj_scroll_to_view(lv_obj_get_child(container, mid_btn_index), LV_ANIM_OFF);
   
    return  container;
}
//-----------------------------------------------------------------------------
static void 
clockTimerCallBack(lv_timer_t *timer)
{
    static const char *week_day[7] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
    static time_t unix_time;
    static struct tm *time_info;
    unix_time = time(NULL);
    time_info = localtime(&unix_time);

    int year = time_info->tm_year+1900;
    int month = time_info->tm_mon + 1;
    int day = time_info->tm_mday;
    int weekday = time_info->tm_wday;
    int hour = time_info->tm_hour;
    int minutes = time_info->tm_min;
    int second = time_info->tm_sec; 
    if (timer != NULL && timer->user_data != NULL)
    {
        clockPointer * clock = (clockPointer *)(timer->user_data);
        if (clock->timeLabel != NULL)
        {
            lv_label_set_text_fmt(clock->timeLabel, "%02d:%02d:%02d", hour, minutes,second);
        }
        if (clock->dateLabel != NULL)
        {
            lv_label_set_text_fmt(clock->dateLabel, "%s %d.%02d.%02d",week_day[weekday], year, month, day);
        }
    }
}
//-----------------------------------------------------------------------------
//时钟控件
lv_obj_t * clockControl(lv_obj_t * page)
{
//核心画布
    static lv_style_t timeControlStyle;
    lv_style_init(&timeControlStyle);
    lv_style_set_bg_color(&timeControlStyle,lv_color_black());
    lv_style_set_opa(&timeControlStyle, LV_OPA_COVER);
    lv_style_set_text_color(&timeControlStyle,lv_color_white());
    lv_obj_t *timeControl  = lv_label_create(page);
    lv_obj_set_size(timeControl,170,60);
    lv_obj_add_style(timeControl,&timeControlStyle,0);
    lv_obj_set_flex_flow(timeControl, LV_FLEX_FLOW_COLUMN);
//时分秒
    static lv_style_t hourControlStyle;
    lv_style_init(&hourControlStyle);
    LV_FONT_DECLARE(lv_font_montserrat_30)
    lv_style_set_text_font(&hourControlStyle,&lv_font_montserrat_30);
    lv_style_set_text_color(&hourControlStyle,lv_color_white());
    lv_obj_t *hourTimeLabel  = lv_label_create(timeControl);
    lv_obj_add_style(hourTimeLabel,&hourControlStyle,0);
//星期年月日
    static lv_style_t dayControlStyle;
    lv_style_init(&dayControlStyle);
    lv_obj_t *dayTimeLabel  = lv_label_create(timeControl);
    lv_style_set_text_color(&dayControlStyle,lv_color_white());
    lv_obj_add_style(dayTimeLabel,&dayControlStyle,0);

//设置时间回调刷新时间显示
    static clockPointer pointerData;
    pointerData.dateLabel   = dayTimeLabel;
    pointerData.timeControl = timeControl;
    pointerData.timeLabel = hourTimeLabel;
    lv_timer_create(clockTimerCallBack, 100, (void *)&pointerData); // 创建定时任务，200ms刷新一次
    return timeControl;
}
//-----------------------------------------------------------------------------
//主状态显示器
lv_obj_t * 
mainStatuslindicator(lv_obj_t *page)
{
    lv_obj_t * statuslindicator = lv_obj_create(page);
    lv_obj_set_flex_flow(statuslindicator, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(statuslindicator,5, LV_PART_MAIN); 
    lv_obj_t * dianLiangIcon   = lv_img_create(statuslindicator);
    lv_img_set_src(dianLiangIcon,&dianliang);
    lv_obj_t * wifiStateOnIcon = lv_img_create(statuslindicator);
    lv_img_set_src(wifiStateOnIcon,&wifistateOn);
    lv_obj_set_size(statuslindicator,30,30);
    return statuslindicator;
}








