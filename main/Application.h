#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include "LinkManager.h"
class Application
{
public:
    Application();
    ~Application();
    static Application*  _app; 
    //Init All Module
    void appInit();

    LinkManager * link() {return this->linkManager;}
private:
    LinkManager *linkManager=nullptr;
};
Application* app(void);
#endif//APPLICATION_H
