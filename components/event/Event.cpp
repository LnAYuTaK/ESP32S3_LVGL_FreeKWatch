
#include "Event.h"
ESPEventID::ESPEventID(int32_t event_id)
                    ,id(event_id)
{

}
ESPEvent::ESPEvent(esp_event_base_t event_base, const ESPEventID &event_id)
            :base(event_base)
            ,id(event_id)
{

}
//------------------------------------------------------------------------
ESPEventReg::ESPEventReg(std::function<void(const ESPEvent &, void*)> cb,
                        const ESPEvent& ev,
                        std::shared_ptr<EventAPI> api)
                        :cb(cb)
                        ,event(ev)
                        ,api(api)
{
    esp_err_t reg_result = api->handler_register(ev.base, ev.id.id(), event_handler_hook, this, &instance);
}

ESPEventReg::~ESPEventReg()
{
    api->handler_unregister(event.base, event.id.get_id(), instance);
}

void ESPEventReg::dispatch_event_handling(ESPEvent event, void *event_data)
{
    cb(event, event_data);
}

void ESPEventReg::event_handler_hook(void *handler_arg,
                                            esp_event_base_t event_base,
                                            int32_t event_id,
                                            void *event_data)
{
    ESPEventReg *object = static_cast<ESPEventReg*>(handler_arg);
    object->dispatch_event_handling(ESPEvent(event_base, ESPEventID(event_id)), event_data);
}

ESPEventLoop::ESPEventLoop()
{
  std::shared_ptr<EventAPI> api = std::make_shared<EventAPIDefault>()
}
ESPEventLoop::~ESPEventLoop() { }
unique_ptr<ESPEventReg> ESPEventLoop::register_event(const ESPEvent &event,
                                   function<void(const ESPEvent &, void*)> cb)
{
    return unique_ptr<ESPEventReg>(new ESPEventReg(cb, event, api));
}

void ESPEventLoop::post_event_data(const ESPEvent &event,
        const chrono::milliseconds &wait_time)
{
    esp_err_t result = api->post(event.base,
            event.id.get_id(),
            nullptr,
            0,
            convert_ms_to_ticks(wait_time));

    if (result != ESP_OK) {
        throw ESPException(result);
    }
}


