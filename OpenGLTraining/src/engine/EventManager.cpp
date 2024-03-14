#include "EventManager.h"
std::vector<std::unique_ptr<EventManager::EventSubscriptionBase>> EventManager::_subscriptions;