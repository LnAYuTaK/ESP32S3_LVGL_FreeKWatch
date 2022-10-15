#include "Application.h"
#include "LinkManager.h"
#include "esp_event_api.h"
Application *Application::_app=nullptr;
Application::Application()
{
    _app = this;
}
//------------------------------------------------------------------------
Application::~Application()
{

}
//------------------------------------------------------------------------
void 
Application::appInit()
{ 
//初始化LVGL
//    lv_init();
//    //初始化LVGL显示端口
//    lv_port_disp_init();
//    //初始化文件系统
//    lv_fs_if_init();
   //连接系统
   
   linkManager = new LinkManager();
   //
}
//------------------------------------------------------------------------
//单例公共接口
Application* app(void)
{
    return Application::_app;
}



