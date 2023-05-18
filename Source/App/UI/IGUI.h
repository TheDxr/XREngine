#pragma once


class IGUI
{
public:
    virtual void Render() = 0;
    virtual void Init() = 0;
    virtual ~IGUI() = default;
};
