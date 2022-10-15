#ifndef ESP_EVENT_API_HPP_
#define ESP_EVENT_API_HPP_

#include "esp_event.h"
#include "esp_event_base.h"
class ESPEventAPI {
public:
    virtual ~ESPEventAPI() { }

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


class ESPEventAPIDefault : public ESPEventAPI {
public:
    ESPEventAPIDefault();
    virtual ~ESPEventAPIDefault();

    ESPEventAPIDefault(const ESPEventAPIDefault &o) = delete;
    ESPEventAPIDefault& operator=(const ESPEventAPIDefault&) = delete;

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


class ESPEventAPICustom : public ESPEventAPI {
public:

    ESPEventAPICustom(const esp_event_loop_args_t &event_loop_args);

    virtual ~ESPEventAPICustom();

    ESPEventAPICustom(const ESPEventAPICustom &o) = delete;
    ESPEventAPICustom& operator=(const ESPEventAPICustom&) = delete;

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

    esp_err_t run(TickType_t ticks_to_run);

private:
    esp_event_loop_handle_t event_loop;
};

#endif // ESP_EVENT_API_HPP_
