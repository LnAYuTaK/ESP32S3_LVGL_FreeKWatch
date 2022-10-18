
#include "EventApi.h"
EventAPIDefault::EventAPIDefault()
{
    //创建事件循环
    esp_err_t res = esp_event_loop_create_default();
}

EventAPIDefault::~EventAPIDefault()
{
    esp_event_loop_delete_default();
}

//esp_event_base_t 事件基  //TIMER_EVENT ? WIFI_EVENT?
//event_id     Event的枚举事件
//handler处理程序功能，当事调度 
//arg 传递进去的参数
//instance 管理生命周期
esp_err_t EventAPIDefault::handler_register(esp_event_base_t event_base,
        int32_t event_id,
        esp_event_handler_t event_handler,
        void *event_handler_arg,
        esp_event_handler_instance_t *instance)
{
    //注册自带默认的事件循环的方式
    return esp_event_handler_instance_register(event_base,
                                               event_id,
                                               event_handler,
                                               event_handler_arg,
                                               instance);
}

esp_err_t EventAPIDefault::handler_unregister(esp_event_base_t event_base,
        int32_t event_id,
        esp_event_handler_instance_t instance)
{
    return esp_event_handler_instance_unregister(event_base, event_id, instance);
}

esp_err_t EventAPIDefault::post(esp_event_base_t event_base,
        int32_t event_id,
        void* event_data,
        size_t event_data_size,
        TickType_t ticks_to_wait)
{  
    //post 回调post to
    return esp_event_post(event_base,
                          event_id,
                          event_data,
                          event_data_size,
                          ticks_to_wait);

}

// ESPEventAPICustom::ESPEventAPICustom(const esp_event_loop_args_t &event_loop_args)
// {
//     //创建事件循环
//     esp_err_t res = esp_event_loop_create(&event_loop_args, &event_loop);
// }

// ESPEventAPICustom::~ESPEventAPICustom()
// {
//     esp_event_loop_delete(event_loop);
// }
// esp_err_t ESPEventAPICustom::handler_register(esp_event_base_t event_base,
//         int32_t event_id,
//         esp_event_handler_t event_handler,
//         void *event_handler_arg,
//         esp_event_handler_instance_t *instance)
// {
//     return esp_event_handler_instance_register_with(event_loop,
//                                                     event_base,
//                                                     event_id,
//                                                     event_handler,
//                                                     event_handler_arg,
//                                                     instance);
// }

// esp_err_t ESPEventAPICustom::handler_unregister(esp_event_base_t event_base,
//         int32_t event_id,
//         esp_event_handler_instance_t instance)
// {
//     return esp_event_handler_instance_unregister_with(event_loop, event_base, event_id, instance);
// }

// esp_err_t ESPEventAPICustom::post(esp_event_base_t event_base,
//         int32_t event_id,
//         void* event_data,
//         size_t event_data_size,
//         TickType_t ticks_to_wait)
// {
//     return esp_event_post_to(event_loop,
//                              event_base,
//                              event_id,
//                              event_data,
//                              event_data_size,
//                              ticks_to_wait);
// }

// esp_err_t ESPEventAPICustom::run(TickType_t ticks_to_run)
// {
//     return esp_event_loop_run(event_loop, ticks_to_run);
// }

