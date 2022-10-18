#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#ifdef __cplusplus 
}
#endif

#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <exception>
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
//EventAPI的子类有两个  一个是系统默认的事件，一个是自定义的事件
class EventAPI {
public:
    virtual ~EventAPI() { }

    virtual esp_err_t handler_register(esp_event_base_t event_base,
            int32_t event_id,
            esp_event_handler_t event_handler,
            void* event_handler_arg,
            esp_event_handler_instance_t *instance) = 0;

    virtual esp_err_t handler_unregister(esp_event_base_t event_base,
            int32_t event_id,
            esp_event_handler_instance_t instance) = 0;

    virtual esp_err_t post(esp_event_base_t event_base,
            int32_t event_id,
            void* event_data,
            size_t event_data_size,
            TickType_t ticks_to_wait) = 0;

};
class EventAPIDefault : public EventAPI {
  public:
        EventAPIDefault();
        virtual ~EventAPIDefault();

        EventAPIDefault(const EventAPIDefault &o) = delete;
        EventAPIDefault& operator=(const EventAPIDefault&) = delete;

        esp_err_t handler_register(esp_event_base_t event_base,
                int32_t event_id,
                esp_event_handler_t event_handler,
                void* event_handler_arg,
                esp_event_handler_instance_t *instance) override;

        esp_err_t handler_unregister(esp_event_base_t event_base,
                int32_t event_id,
                esp_event_handler_instance_t instance) override;

        esp_err_t post(esp_event_base_t event_base,
                int32_t event_id,
                void* event_data,
                size_t event_data_size,
                TickType_t ticks_to_wait) override;
};


// class EventAPICustom : public EventAPI {
// public:

//     EventAPICustom(const esp_event_loop_args_t &event_loop_args);

//     virtual ~EventAPICustom();

//     //不允许拷贝构造
//     EventAPICustom(const EventAPICustom &o) = delete;
//     EventAPICustom& operator=(const ESPEventAPICustom&) = delete;

//     esp_err_t handler_register(esp_event_base_t event_base,
//             int32_t event_id,
//             esp_event_handler_t event_handler,
//             void* event_handler_arg,
//             esp_event_handler_instance_t *instance) override;

//     esp_err_t handler_unregister(esp_event_base_t event_base,
//             int32_t event_id,
//             esp_event_handler_instance_t instance) override;

//     esp_err_t post(esp_event_base_t event_base,
//             int32_t event_id,
//             void* event_data,
//             size_t event_data_size,
//             TickType_t ticks_to_wait) override;

//     esp_err_t run(TickType_t ticks_to_run);

// private:
//     esp_event_loop_handle_t event_loop;
// };


