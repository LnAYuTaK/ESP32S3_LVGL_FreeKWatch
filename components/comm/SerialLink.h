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
#include "driver/gpio.h"
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
    SerialConfig();
    //Get      
    uart_port_t            portName ()         { return _portName; }
    uart_config_t *        uartConfig()        { return &_uart_config;}
    //Set
    inline esp_err_t setBaud           (int baud);
    inline esp_err_t setDataBits       (uart_word_length_t dataBits);
    inline esp_err_t setFlowControl    (uart_hw_flowcontrol_t type,uint8_t rx_thresh);         
    inline esp_err_t setStopBits       (uart_stop_bits_t stopBits);
    inline esp_err_t setParity         (uart_parity_t parity);   
    inline void      setRTBufSize      (int bufSize);
    inline void      setPortName       (uart_port_t portName); 
    inline void      setRxPinNum       (const int RxPinNum);
    inline void      setTxPinNum       (const int TXPinNum);
    //override
    LinkType  type   (){return LinkType::TypeSerial; }
private:
    uart_port_t      _portName;
    uart_config_t    _uart_config;
    int              _rtBufSize;
    int              _RxPinNum;
    int              _TxPinNum;
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
    int  writeBytes  (char *buf,int len )override;
private:
    void _readBytes  ();
    SerialConfig*    _serialConfig;
    int              _bytesRead ;     
    int              _timeout ;
    volatile bool    _stopp ;               
    char *           _transmitBuffer;                
    bool             _serialLinkState;
    //



};

#endif //SERIALLINK_H