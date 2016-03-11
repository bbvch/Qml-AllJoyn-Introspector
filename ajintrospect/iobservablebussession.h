#pragma once

#include <memory>
#include <string>
#include <functional>

#include "argumentlist.h"

class IObservableBusSession
{
public:
    using CallbackType = std::function<void(std::string)>;

    virtual void addTerminationCallback(void*, CallbackType) = 0;
    virtual void removeTerminationCallback(void*) = 0;
    virtual std::string getFullName() const = 0;
    virtual bool isTerminated() const = 0;
    virtual std::unique_ptr<ArgumentList> invokeMethod(std::string path, std::string method, std::unique_ptr<ArgumentList> args = nullptr) = 0;
    virtual std::unique_ptr<ArgumentList> createArgs() const = 0;
};
