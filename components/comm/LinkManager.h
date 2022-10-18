#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <functional>
#include <list>
#include <vector>
//C
#include "esp_err.h"
#include "LinkConfig.h"
#include "LinkInterface.h"
#include "SerialLink.h"
#include "EventApi.h"
using namespace std;
///
/// \brief 负责生成并管理Link
///
class LinkManager   //Singleton
{
public:
    LinkManager();
    //创建Link配置统一接口
    SharedLinkConfigPtr createLinkConf(int type);
    //创建Link连接接口
    bool  createLink(SharedLinkConfigPtr config);
private:
    //Save Link  List
    list<SharedLinkConfigPtr>    _LinkConfigList;
    list<SharedLinkInterfacePtr> _LinkInterfaceList;


};

#endif // LINKMANAGER_H
