#include "SerialLink.h"
//Setting 中读取

#define RXPinNum 18
#define TXPinNum 17
#define PortNum  UART_NUM_0
#define UARTBUFSIZE (2048)
SerialConfig::SerialConfig()
    :LinkConfig()
    ,_portName(PortNum)
    ,_rtBufSize(UARTBUFSIZE)
    ,_RxPinNum(RXPinNum)
    ,_TxPinNum(TXPinNum)
{
    //default Setting
    _uart_config.baud_rate  = 115200;
    _uart_config.data_bits  = UART_DATA_8_BITS;
    _uart_config.parity     = UART_PARITY_DISABLE;
    _uart_config.stop_bits  = UART_STOP_BITS_1;
    _uart_config.flow_ctrl  = UART_HW_FLOWCTRL_DISABLE;
    _uart_config.source_clk = UART_SCLK_APB;
} 
//
esp_err_t 
SerialConfig::setBaud(int baud)
{
    return uart_set_baudrate(_portName,baud);
}
//------------------------------------------------------------------------
esp_err_t 
SerialConfig::setFlowControl(uart_hw_flowcontrol_t type,uint8_t rx_thresh)
{
   return uart_set_hw_flow_ctrl(_portName,type,rx_thresh);
}
//------------------------------------------------------------------------
esp_err_t 
SerialConfig::setStopBits(uart_stop_bits_t stopBits)
{
    return uart_set_stop_bits(_portName,stopBits);
}
//------------------------------------------------------------------------
esp_err_t 
SerialConfig::setParity(uart_parity_t parity)
{
   return uart_set_parity(_portName,parity);
}
//------------------------------------------------------------------------
esp_err_t 
SerialConfig::setDataBits(uart_word_length_t dataBits)
{
    return uart_set_word_length(_portName,dataBits);
}
//------------------------------------------------------------------------
void 
SerialConfig::setPortName(uart_port_t portName)
{
    if(portName <= UART_NUM_MAX-1) {
        _portName= portName;
    }
}
//------------------------------------------------------------------------
void 
SerialConfig::setRTBufSize(const int bufSize)
{
    bufSize>2048?(_rtBufSize = 2048):(_rtBufSize = bufSize);
}
//------------------------------------------------------------------------
void
SerialConfig::setRxPinNum(const int RxPinNum)
{
    
    if(RxPinNum<=48){
        _RxPinNum = RxPinNum;
    }
}
//------------------------------------------------------------------------
void
SerialConfig::setTxPinNum(const int TxPinNum)
{
    if(TxPinNum<=48){
        _TxPinNum = TxPinNum;
    }
}
//------------------------------------------------------------------------
SerialLink::SerialLink(SharedLinkConfigPtr& config)
    :LinkInterface(config)
    ,_serialConfig(static_cast<SerialConfig*>(config.get()))
    ,_bytesRead(0)
    ,_stopp(false)
    ,_serialLinkState(false)
{ 

}
//------------------------------------------------------------------------
SerialLink::~SerialLink()
{
    disconnect();
}
//------------------------------------------------------------------------
bool
SerialLink::connect()
{
    uart_driver_install(_serialConfig->portName(),UARTBUFSIZE, 0, 0, NULL, 0);
    uart_param_config(_serialConfig->portName(),_serialConfig->uartConfig());
    //uart_set_pin(_serialConfig->portName(),TXPinNum,RXPinNum,UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    return uart_is_driver_installed(_serialConfig->portName());
}
//------------------------------------------------------------------------
void 
SerialLink::disconnect()
{
    if(uart_is_driver_installed(_serialConfig->portName())) {
        uart_driver_delete(_serialConfig->portName());
    }
}
//------------------------------------------------------------------------
int 
SerialLink::writeBytes(char *buf,int len)
{
  return uart_write_bytes(_serialConfig->portName(),buf,len);
}
//------------------------------------------------------------------------




