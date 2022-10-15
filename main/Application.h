#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
class LinkManager;
class PageManager;
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
    PageManager *pageManager=nullptr;
};
Application* app(void);
#endif//APPLICATION_H
