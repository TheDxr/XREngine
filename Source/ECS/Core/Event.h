#pragma once

#include "Ecs.h"

#include <any>
#include <unordered_map>

namespace ecs
{

class Event
{
public:
    Event() = delete;

    explicit Event(EventId type) : type_(type) {}

    template <typename T>
    void setParam(EventId id, T value)
    {
        data_[id] = value;
    }

    template <typename T>
    T getParam(EventId id)
    {
        return std::any_cast<T>(data_[id]);
    }

    EventId getType() const { return type_; }

private:
    EventId type_{};
    std::unordered_map<EventId, std::any> data_{};
};
}