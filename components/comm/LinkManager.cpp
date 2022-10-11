#include "LinkManager.h"

LinkManager::LinkManager()
{
  //初始化WIFI 并连接
  


    
}
//------------------------------------------------------------------------
SharedLinkConfigPtr
LinkManager::createLinkConf(uart_port_t portName,int type)
{
    LinkConfig  *conf =nullptr;
    switch(type){
        case LinkConfig::TypeSerial:
            conf = new SerialConfig(portName);
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
    }
    link.get()->connect();
    string str = "Hello world";
    vector<char> vec0(str.begin(), str.end()); 
    link.get()->writeBytes(vec0);
    return true;
}
















