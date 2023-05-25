#pragma once
#include <functional>
#include <list>
#include <unordered_map>
#include "Ecs.h"
#include "Event.h"

namespace ecs
{

class EventManager
{
public:
    void addListener(EventId eventId, std::function<void(Event &)> const &listener)
    {
        listenerMap[eventId].push_back(listener);
    }

    void sendEvent(Event &event)
    {
        uint32_t type = event.getType();

        for(auto const &listener : listenerMap[type]) {
            listener(event);
        }
    }

    void sendEvent(EventId eventId)
    {
        Event event(eventId);

        for(auto const &listener : listenerMap[eventId]) {
            listener(event);
        }
    }

private:
    // listeners == std::list<std::function<void(Event &)>>
    // listener == std::function<void(Event &)>
    std::unordered_map<EventId, std::list<std::function<void(Event &)>>> listenerMap;
};
} // namespace ecs