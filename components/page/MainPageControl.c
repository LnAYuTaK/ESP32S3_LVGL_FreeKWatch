#include "MainPageControl.h"
#include "time.h"
#include "aiImg.c"
#include "dianhua.c"
#include "gaode.c"
#include "linggan.c"
#include "qianbao.c"
#include "yinle.c"
#include "zhanghu.c"

LV_IMG_DECLARE(aiImg);//紫色
LV_IMG_DECLARE(dianhua);//绿色
LV_IMG_DECLARE(gaode);//蓝色
LV_IMG_DECLARE(linggan);//橙色
LV_IMG_DECLARE(qianbao);//黄色
LV_IMG_DECLARE(yinle);//红色
LV_IMG_DECLARE(zhanghu);//青色

lv_obj_t * 
scrollBarControl(lv_obj_t * page)
{
//初始化中间滚动条按键    
    lv_obj_t * container = lv_obj_create(page);
    lv_obj_set_size(container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scroll_snap_x(container, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_style_bg_opa(container, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 3, LV_PART_MAIN);
    lv_obj_set_style_border_color(container ,lv_color_white(),LV_PART_MAIN);
    lv_obj_set_style_pad_column(container,10, LV_PART_MAIN);   
    lv_obj_center(container);

    lv_obj_t* yinleBtn = lv_btn_create(container);
    lv_obj_set_size(yinleBtn, 70, 70);
//注册回调显示界面

    lv_obj_t* lingGanBtn = lv_btn_create(container);
    lv_obj_set_size(lingGanBtn, 70, 70);
    lv_obj_t* qianBaoBtn = lv_btn_create(container);
    lv_obj_set_size(qianBaoBtn, 70, 70);
    lv_obj_t*  dianHuaBtn  = lv_btn_create(container);
    lv_obj_set_size(dianHuaBtn, 70, 70);
    lv_obj_t* zhangHuBtn = lv_btn_create(container);
    lv_obj_set_size(zhangHuBtn, 70, 70);
    lv_obj_t* gaoDeBtn = lv_btn_create(container);
    lv_obj_set_size(gaoDeBtn, 70, 70);
    lv_obj_t* aiImgBtn = lv_btn_create(container);
    lv_obj_set_size(aiImgBtn, 70, 70);
//音乐
    static lv_style_t yinleBtnStyle;
    lv_style_init(&yinleBtnStyle);
    lv_obj_set_style_bg_img_src(yinleBtn,&yinle,0);
    lv_obj_set_style_bg_opa(yinleBtn,LV_OPA_0,0);
    lv_obj_add_style(yinleBtn,&yinleBtnStyle,0);
//灯泡
    static lv_style_t lingGanBtnStyle;
    lv_style_init(&lingGanBtnStyle);
    lv_obj_set_style_bg_img_src(lingGanBtn,&linggan,0);
    lv_obj_set_style_bg_opa(lingGanBtn,LV_OPA_0,0);
    lv_obj_add_style(lingGanBtn,&lingGanBtnStyle,0);
//钱包
    static lv_style_t qianBaoBtnStyle;
    lv_style_init(&qianBaoBtnStyle);
    lv_obj_set_style_bg_img_src(qianBaoBtn,&qianbao,0);
    lv_obj_set_style_bg_opa(qianBaoBtn,LV_OPA_0,0);
    lv_obj_add_style(qianBaoBtn,&qianBaoBtnStyle,0);
//电话
    static lv_style_t  dianHuaBtnStyle;
    lv_style_init(& dianHuaBtnStyle);
    lv_obj_set_style_bg_img_src( dianHuaBtn,&dianhua,0);
    lv_obj_set_style_bg_opa( dianHuaBtn,LV_OPA_0,0);
    lv_obj_add_style(dianHuaBtn,& dianHuaBtnStyle,0);
//账户
    static lv_style_t  zhangHuBtnStyle;
    lv_style_init(& zhangHuBtnStyle);
    lv_obj_set_style_bg_img_src( zhangHuBtn,&zhanghu,0);
    lv_obj_set_style_bg_opa( zhangHuBtn,LV_OPA_0,0);
    lv_obj_add_style(zhangHuBtn,& zhangHuBtnStyle,0);
//高德
    static lv_style_t  gaoDeBtnStyle;
    lv_style_init(& gaoDeBtnStyle);
    lv_obj_set_style_bg_img_src( gaoDeBtn,&gaode,0);
    lv_obj_set_style_bg_opa( gaoDeBtn,LV_OPA_0,0);
    lv_obj_add_style(gaoDeBtn,& gaoDeBtnStyle,0);
//AI
    static lv_style_t  aiImgBtnStyle;
    lv_style_init(& aiImgBtnStyle);
    lv_obj_set_style_bg_img_src( aiImgBtn,&aiImg,0);
    lv_obj_set_style_bg_opa( aiImgBtn,LV_OPA_0,0);
    lv_obj_add_style(aiImgBtn,& aiImgBtnStyle,0);

    uint32_t mid_btn_index = (lv_obj_get_child_cnt(container) - 1) / 2;
    for (uint32_t i = 0; i < mid_btn_index; i++)
    {
        lv_obj_move_to_index(lv_obj_get_child(container, -1), 0);
    }
    /*当按钮数为偶数时，确保按钮居中*/
    lv_obj_scroll_to_view(lv_obj_get_child(container, mid_btn_index), LV_ANIM_OFF);
    // lv_group_add_obj(group,yinleBtn);
    // lv_group_add_obj(group,lingGanBtn);
    // lv_group_add_obj(group,qianBaoBtn);
    // lv_group_add_obj(group,dianHuaBtn);
    // lv_group_add_obj(group,zhangHuBtn);
    // lv_group_add_obj(group,gaoDeBtn);
    // lv_group_add_obj(group,aiImgBtn);
    lv_group_add_obj(group,container);
    return container;
}

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

//时钟控件
clockPointer * 
clockControl(lv_obj_t * page)
{
//核心画布
    static lv_style_t timeControlStyle;
    lv_style_init(&timeControlStyle);
    lv_style_set_bg_color(&timeControlStyle,lv_color_black());
    lv_style_set_opa(&timeControlStyle, LV_OPA_COVER);
    lv_obj_t *timeControl  = lv_label_create(page);
    lv_obj_set_size(timeControl,150,60);
    lv_obj_add_style(timeControl,&timeControlStyle,0);
    lv_obj_set_flex_flow(timeControl, LV_FLEX_FLOW_COLUMN);
    lv_obj_align(timeControl, LV_ALIGN_TOP_MID, 0,30);
//时分秒
    static lv_style_t hourControlStyle;
    lv_style_init(&hourControlStyle);
    LV_FONT_DECLARE(lv_font_montserrat_30)
    lv_style_set_text_font(&hourControlStyle,&lv_font_montserrat_30);
    lv_obj_t *hourTimeLabel  = lv_label_create(timeControl);
    lv_obj_add_style(hourTimeLabel,&hourControlStyle,0);
//星期年月日
    static lv_style_t dayControlStyle;
    lv_style_init(&dayControlStyle);
    lv_obj_t *dayTimeLabel  = lv_label_create(timeControl);
    lv_obj_add_style(dayTimeLabel,&dayControlStyle,0);

//设置时间回调刷新时间显示
    static clockPointer pointerData;
    pointerData.dateLabel   = dayTimeLabel;
    pointerData.timeControl = timeControl;
    pointerData.timeLabel = hourTimeLabel;
    lv_timer_t* task_timer = lv_timer_create(clockTimerCallBack, 100, (void *)&pointerData); // 创建定时任务，200ms刷新一次
    return &pointerData;
}
//状态栏//









