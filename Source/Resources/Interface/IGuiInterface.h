#pragma once

// Gui interface
class IGuiInterface
{
public:
    virtual void render() = 0;
    virtual void init() = 0;
    virtual ~IGuiInterface() = default;
};
