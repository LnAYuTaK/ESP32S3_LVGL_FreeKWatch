#include "wifi.h"


static const char *TAG = "NET";

//查询IP
void 
task_wifi_scan(void *arg){
    uint16_t num;
    wifi_ap_record_t records[8];
    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_num(&num);
    if(num > 8){
        num = 8;	
    }
    esp_wifi_scan_get_ap_records(&num, records);
    if(num > 8){
        num = 8;	
    }
    for(int i = 0; i < num; i++){
        uint8_t rssi_level = 0;
        switch (records[i].rssi) {
            case -100 ... -88:
                rssi_level = 1; break;
            case -87 ... -77:
                rssi_level = 2; break;
            case -76 ... -66:
                rssi_level = 3; break;
            case -65 ... -55:
                rssi_level = 4; break;
            default:
                if(records[i].rssi < -100){
                    rssi_level = 0;
                }else{
                    rssi_level = 5;
                }
                break;
        }
	// 逐条打印扫描到的WiFi
        printf("—————【第 %2d 个WiFi】———————\n", i+1);
        printf("WiFi名称: %s\n", records[i].ssid);
        printf("信号强度: %d格\n", rssi_level);
        printf("WiFi: 安全类型: %d\n\n", records[i].authmode);
    }
}
//------------------------------------------------------------------------
void    //WIFI 的回调
wifiEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) 
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}
//------------------------------------------------------------------------
static void 
init_nvs() 
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}
//------------------------------------------------------------------------
static void 
wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifiEventHandler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifiEventHandler,
                                                        NULL,
                                                        &instance_got_ip));



    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
            /* Setting a password implies station will connect to all security modes including WEP/WPA.
             * However these modes are deprecated and not advisable to be used. Incase your Access point
             * doesn't support WPA2, these mode can be enabled by commenting below line */
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}
//-------------------------------------------------------
static void 
initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    sntp_stop();
    sntp_enabled();
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_setservername(3, "cn.pool.ntp.org"); // 中国区NTP服务的虚拟集群
    sntp_setservername(1, "210.72.145.44"); // 国家授时中心服务器 IP 地址
    sntp_setservername(2, "ntp1.aliyun.com");
    sntp_init();
}
//------------------------------------------------------------------------
static void 
obtain_time()
{
    initialize_sntp();
    time_t now = 0;
    struct tm timeinfo = {0};
    int retry = 0;
    const int retry_count = 10;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count)
    {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    time(&now);
    localtime_r(&now, &timeinfo);
}
//-------------------------------------------------------
void 
netInit()
{ 
    time_t now;         
    struct tm timeinfo; 
    //初始化NVS
    init_nvs();
    wifi_init_sta();
    //时间获取
    obtain_time(); 
    time(&now);                   //获取总秒数时间
    localtime_r(&now, &timeinfo); //将now unix时间戳格式转为timeinfo时间结构体
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900)) //判断timeinfo是否正确否者重新获取
    {
        ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time over NTP.");
        obtain_time(); //获取时间
        // update 'now' variable with current time
        time(&now); //获取总秒数时间
    }
        time(&now);//获取unix时间戳
        setenv("TZ", "CST-8", 1);//设置为东八区，中国是东八区
        tzset();
        localtime_r(&now, &timeinfo);//转为tm结构体
        ESP_LOGI(TAG, "实时时间：周%d,%d年:%d月:%d日,%d:%d:%d", timeinfo.tm_wday, timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
}

//------------------------------------------------------------------------

