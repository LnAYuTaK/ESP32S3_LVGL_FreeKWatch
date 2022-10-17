#include "LinkManager.h"

//Setting 中读取
#define RXPinNum 18
#define TXPinNum 17
#define PortNum  1
LinkManager::LinkManager()
{

}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
SharedLinkConfigPtr
LinkManager::createLinkConf(int type)
{
    LinkConfig  *conf =nullptr;
    switch(type) {
        case LinkConfig::TypeSerial:
            conf = new SerialConfig(PortNum,RXPinNum,TXPinNum);
            _LinkConfigList.push_back(SharedLinkConfigPtr(conf));
            break;
    }
    if(conf) {
        return _LinkConfigList.back();
    }
    return nullptr;
}
//------------------------------------------------------------------------
bool 
LinkManager::createLink(SharedLinkConfigPtr config)
{
    SharedLinkInterfacePtr link = nullptr;
    switch(config->type()) {
    case LinkConfig::TypeSerial:
        link = make_shared<SerialLink>(config);
        break;
    case LinkConfig::TypeUdp:
        break;
    case LinkConfig::TypeTcp:
        break;
    case LinkConfig::TypeBluetooth:
        break;
    case LinkConfig::TypeDefault:
        break;
    case LinkConfig::TypeWifi:
        break;
    }
    link.get()->connect();
    return true;
}
















