#ifndef LINKCONFIG_H
#define LINKCONFIG_H

#include <iostream>
#include <string>
#include <memory>
using namespace std;
class LinkInterface;
///
/// \brief 连接配置
///
class LinkConfig 
{
public:
    LinkConfig(); 
    enum LinkType{
        TypeTcp,
        TypeUdp,
        TypeSerial,
        TypeBluetooth,
        TypeDefault
    };
    virtual LinkType type() = 0;
};
typedef shared_ptr<LinkConfig>  SharedLinkConfigPtr;
#endif // LINKCONFIG_H
