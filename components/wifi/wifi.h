
#ifndef WIFI_H
#define WIFI_H
#include <string.h>
#include <time.h>
#include <sys/time.h>

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
#include "esp_system.h"
#include "esp_sntp.h"
//默认账号密码
#define EXAMPLE_ESP_WIFI_SSID      "YTYDHY"
#define EXAMPLE_ESP_WIFI_PASS      "ydhy160725"
#define EXAMPLE_ESP_MAXIMUM_RETRY  10
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
/// WifiLink configuration

void netInit();
void task_wifi_scan(void *arg);
#endif

