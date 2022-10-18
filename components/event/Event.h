
#ifndef ESP_EVENT_CXX_H_
#define ESP_EVENT_CXX_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "esp_timer.h"
#include "esp_err.h"
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
#include "EventApi.h"

class ESPEventID {
public:
    ESPEventID(int32_t event_id);
    inline int32_t id() const {return _id;}
private:
    int32_t _id;
};


class ESPEvent
{
public:
    ESPEvent(esp_event_base_t event_base, const ESPEventID &event_id);
    esp_event_base_t base(){return _base;}

private:
    esp_event_base_t _base;
    ESPEventID id;
};

class ESPEventReg {
public:

    ESPEventReg(std::function<void(const ESPEvent &, void*)> cb,
            const ESPEvent& ev,
            std::shared_ptr<EventAPI> api);

    virtual ~ESPEventReg();

protected:

    static void event_handler_hook(void *handler_arg,
                                   esp_event_base_t event_base,
                                   int32_t event_id,
                                   void *event_data);

    std::function<void(const ESPEvent &, void*)> cb;
    virtual void dispatch_event_handling(ESPEvent event, void *event_data);
    ESPEvent event;
    std::shared_ptr<EventAPI> api;
    esp_event_handler_instance_t instance;
};

class ESPEventLoop {
public:

    ESPEventLoop();

    virtual ~ESPEventLoop();
    std::unique_ptr<ESPEventReg> register_event(const ESPEvent &event,
            std::function<void(const ESPEvent &, void*)> cb);
    template<typename T>
    void post_event_data(const ESPEvent &event,
            T &event_data,
            const std::chrono::milliseconds &wait_time = PLATFORM_MAX_DELAY_MS);

    void post_event_data(const ESPEvent &event,
            const std::chrono::milliseconds &wait_time = PLATFORM_MAX_DELAY_MS);

private:
    std::shared_ptr<EventAPI> api;
};

template<typename T>
void ESPEventLoop::post_event_data(const ESPEvent &event,
        T &event_data,
        const std::chrono::milliseconds &wait_time)
{
    esp_err_t result = api->post(event.base,
            event.id.get_id(),
            &event_data,
            sizeof(event_data),
            convert_ms_to_ticks(wait_time));

    if (result != ESP_OK) {
        throw ESPException(result);
    }
}

#endif // __cpp_exceptions
