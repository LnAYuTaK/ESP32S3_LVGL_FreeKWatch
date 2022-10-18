#include "LinkManager.h"
ESP_EVENT_DEFINE_BASE(TIMER_EVENTS);

LinkManager::LinkManager()
{

}

//------------------------------------------------------------------------
SharedLinkConfigPtr 
LinkManager::createLinkConf(int type)
{
    cout << "Create LinkConf" << endl;
    LinkConfig  *conf =nullptr;
    switch(type) {
        case LinkConfig::TypeSerial:
            conf = new SerialConfig();
            _LinkConfigList.push_back(SharedLinkConfigPtr(conf));
            break;
    }
    if(conf){
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
    if(link) {
       link.get()->connect();
       return true;
    }
    return false;
}
//------------------------------------------------------------------------











