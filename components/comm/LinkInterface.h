#ifndef LINKINTERFACE_H
#define LINKINTERFACE_H
#include <iostream>
#include <vector>
#include <memory>
#include "LinkConfig.h"
using namespace std;
class LinkInterface 
{
public:
    virtual ~LinkInterface     ();
    virtual bool connect       (void) = 0;
    virtual void disconnect    (void) = 0;
    virtual bool isConnected   (void) const = 0;
    virtual int  writeBytes    (char *buf,int len) = 0;
    //virtual void readBytes   (vector<char> &byteData) = 0;
protected:
    LinkInterface(SharedLinkConfigPtr &config); 
};
typedef shared_ptr<LinkInterface>  SharedLinkInterfacePtr;

#endif //LINKINTERFACE_H


