#pragma once
#include <string>

class Window {
public:
    virtual void init() = 0;
    virtual bool update() = 0;
    virtual void postUpdate() = 0;
    // title
    virtual void setTitle(std::string title) = 0;
    virtual std::string getTitle() = 0;
    virtual void close() = 0;
};