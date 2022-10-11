#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <iostream>
#include <string>
#include <vector>
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <sys/fcntl.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#ifdef __cplusplus
}
#endif

#include "LinkConfig.h"
#include "LinkInterface.h"
using namespace std;
/// SerialLink configuration
class SerialConfig : public LinkConfig
{
public:
    SerialConfig(uart_port_t portName);
    //Get      
    uart_port_t            portName ()         { return _portName; }
    uart_config_t *        uartConfig()        { return &uart_config;}
    //Set
    esp_err_t setBaud           (int baud);
    esp_err_t setDataBits       (uart_word_length_t dataBits);
    esp_err_t setFlowControl    (uart_hw_flowcontrol_t type,uint8_t rx_thresh);         
    esp_err_t setStopBits       (uart_stop_bits_t stopBits);
    esp_err_t setParity         (uart_parity_t parity);     
    void      setPortName       (uart_port_t portName);          
    //override
    LinkType  type         () {return LinkType::TypeSerial; }
private:
    uart_port_t   _portName;
    uart_config_t uart_config;
};

class SerialLink : public LinkInterface
{
public:
    SerialLink(SharedLinkConfigPtr& config);
    virtual ~SerialLink();
    // LinkInterface overrides
    bool connect     ()override;
    void disconnect  ()override;
    bool isConnected ()const override {return _serialLinkState;}
    int  writeBytes  (vector<char> &byteData)override;
private:
    void _readBytes  ();
    SerialConfig*    _serialConfig;
    int              _bytesRead ;     
    int              _timeout ;
    volatile bool    _stopp ;               
    char *           _transmitBuffer;                
    bool             _serialLinkState;
};

#endif //SERIALLINK_H