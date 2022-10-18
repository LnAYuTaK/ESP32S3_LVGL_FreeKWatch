#include "Application.h"
#include "LinkManager.h"
#include "PageManager.h"
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
   linkManager = new LinkManager();
   pageManager = new PageManager();
   //
}
//------------------------------------------------------------------------
//单例公共接口
Application* app(void)
{
    return Application::_app;
}



