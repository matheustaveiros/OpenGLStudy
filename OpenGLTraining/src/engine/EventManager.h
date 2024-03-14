#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
#include "BaseEvent.h"

class EventManager
{
private:
    struct EventSubscriptionBase
    {
        virtual ~EventSubscriptionBase() = default;
        virtual void call(const BaseEvent* event) const = 0;
    };

    template<typename T, typename = std::enable_if_t<std::is_base_of_v<BaseEvent, T>>>
    struct EventSubscription : public EventSubscriptionBase
    {
        std::function<void(const T&)> callback;

        explicit EventSubscription(std::function<void(const T&)> callback) : callback(callback) {}

        void call(const BaseEvent* event) const override
        {
            callback(*dynamic_cast<const T*>(event));
        }
    };

    static std::vector<std::unique_ptr<EventSubscriptionBase>> _subscriptions;

public:
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<BaseEvent, T>>>
    static void Subscribe(std::function<void(const T&)> callback)
    {
        _subscriptions.push_back(std::make_unique<EventSubscription<T>>(callback));
    }

    template<typename T, typename = std::enable_if_t<std::is_base_of_v<BaseEvent, T>>>
    static void Unsubscribe(std::function<void(const T&)> callback)
    {
        auto it = std::remove_if(_subscriptions.begin(), _subscriptions.end(), [&](const auto& subscription)
            {
            auto derivedSubscription = dynamic_cast<EventSubscription<T>*>(subscription.get());
            return derivedSubscription && derivedSubscription->callback.target_type() == callback.target_type();
            });
        _subscriptions.erase(it, _subscriptions.end());
    }

    template<typename T, typename = std::enable_if_t<std::is_base_of_v<BaseEvent, T>>>
    static void Dispatch(const T& event)
    {
        for (const auto& subscription : _subscriptions)
        {
            if (auto derivedSubscription = dynamic_cast<EventSubscription<T>*>(subscription.get()))
            {
                derivedSubscription->call(&event);
            }
        }
    }
};