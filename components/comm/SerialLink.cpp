#include "SerialLink.h"
SerialConfig::SerialConfig(uart_port_t portName)
    :LinkConfig()
    ,_portName(portName)
{
    //default Setting
    uart_config.baud_rate  = 115200;
    uart_config.data_bits  = UART_DATA_8_BITS;
    uart_config.parity     = UART_PARITY_DISABLE;
    uart_config.stop_bits  = UART_STOP_BITS_1;
    uart_config.flow_ctrl  = UART_HW_FLOWCTRL_DISABLE;
    uart_config.source_clk = UART_SCLK_APB;
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
      _portName= portName;
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
    uart_driver_install(_serialConfig->portName(), 2*1024, 0, 0, NULL, 0);
    uart_param_config(_serialConfig->portName(),_serialConfig->uartConfig());
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
SerialLink::writeBytes(vector<char> &byteData)
{
    char *_byteData = &byteData[0];
    return uart_write_bytes(_serialConfig->portName(),(const char *)_byteData,strlen(_byteData));
}
//------------------------------------------------------------------------




