
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

class ESPEventID {
public:
    ESPEventID(int32_t event_id);
    inline int32_t id() const {return id;}
private:
    int32_t id;
};


struct ESPEvent {
    ESPEvent()
        : base(nullptr), id() { }
    ESPEvent(esp_event_base_t event_base, const ESPEventID &event_id)
        : base(event_base), id(event_id) { }

    esp_event_base_t base;
    ESPEventID id;
};

class ESPEventReg {
public:

    ESPEventReg(std::function<void(const ESPEvent &, void*)> cb,
            const ESPEvent& ev,
            std::shared_ptr<ESPEventAPI> api);

    virtual ~ESPEventReg();

protected:

    static void event_handler_hook(void *handler_arg,
                                   esp_event_base_t event_base,
                                   int32_t event_id,
                                   void *event_data);

    /**
     * User event handler.
     */
    std::function<void(const ESPEvent &, void*)> cb;

    /**
     * Helper function to enter the instance's scope from the generic \c event_handler_hook().
     */
    virtual void dispatch_event_handling(ESPEvent event, void *event_data);
    ESPEvent event;

    std::shared_ptr<ESPEventAPI> api;
    esp_event_handler_instance_t instance;
};

class ESPEventRegTimed : public ESPEventReg {
public:

    ESPEventRegTimed(std::function<void(const ESPEvent &, void*)> cb,
            const ESPEvent& ev,
            std::function<void(const ESPEvent &)> timeout_cb,
            const std::chrono::microseconds &timeout,
            std::shared_ptr<ESPEventAPI> api);

    virtual ~ESPEventRegTimed();

protected:
    static void timer_cb_hook(void *arg);

    void dispatch_event_handling(ESPEvent event, void *event_data) override;

    std::function<void(const ESPEvent &)> timeout_cb;
    esp_timer_handle_t timer;


    std::mutex timeout_mutex;
};

class ESPEventLoop {
public:

    ESPEventLoop(std::shared_ptr<ESPEventAPI> api = std::make_shared<ESPEventAPIDefault>());


    virtual ~ESPEventLoop();

    std::unique_ptr<ESPEventReg> register_event(const ESPEvent &event,
            std::function<void(const ESPEvent &, void*)> cb);
    std::unique_ptr<ESPEventRegTimed> register_event_timed(const ESPEvent &event,
            std::function<void(const ESPEvent &, void*)> cb,
            const std::chrono::microseconds &timeout,
            std::function<void(const ESPEvent &)> timer_cb);

    template<typename T>
    void post_event_data(const ESPEvent &event,
            T &event_data,
            const std::chrono::milliseconds &wait_time = PLATFORM_MAX_DELAY_MS);

    void post_event_data(const ESPEvent &event,
            const std::chrono::milliseconds &wait_time = PLATFORM_MAX_DELAY_MS);

private:
    std::shared_ptr<ESPEventAPI> api;
};


class ESPEventHandlerSync {
public:

    struct EventResult {
        EventResult() : event(), ev_data(nullptr) { }
        EventResult(ESPEvent ev, void *ev_data) : event(ev), ev_data(ev_data) { }
        ESPEvent event;
        void *ev_data;
    };

    struct EventResultTimed : public EventResult {
        EventResultTimed(EventResult event_result, bool timeout_arg)
            : EventResult(event_result), timeout(timeout_arg) { }
        bool timeout;
    };

    ESPEventHandlerSync(std::shared_ptr<ESPEventLoop> event_loop,
                        size_t queue_max_size = 10,
                        TickType_t queue_send_timeout = 0);

    virtual ~ESPEventHandlerSync();
    EventResult wait_event();
    EventResultTimed wait_event_for(const std::chrono::milliseconds &timeout);
    void listen_to(const ESPEvent &event);
    size_t get_send_queue_errors() const;

protected:

    void post_event(const EventResult &result);

private:

    std::atomic<size_t> send_queue_errors;

    QueueHandle_t event_queue;

    TickType_t queue_send_timeout;

    std::shared_ptr<ESPEventLoop> event_loop;

    std::vector<std::shared_ptr<ESPEventReg> > registry;
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
