
#ifndef WIFI_H
#define WIFI_H
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#define EXAMPLE_ESP_WIFI_SSID      "YTYDHY"
#define EXAMPLE_ESP_WIFI_PASS      "ydhy160725"
#define EXAMPLE_ESP_MAXIMUM_RETRY  10
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
/// WifiLink configuration
static void wifiEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void task_wifi_scan(void *arg);
void init_nvs();
static const char *TAG = "wifi station";
static int s_retry_num = 0;
static EventGroupHandle_t s_wifi_event_group;
void  wifi_init_sta(void);
//... 正常的声明段
#endif

