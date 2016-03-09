#pragma once

#include <string>
#include <functional>

class IObservableBusSession
{
public:
    using CallbackType = std::function<void(std::string)>;

    virtual void addTerminationCallback(void*, CallbackType) = 0;
    virtual void removeTerminationCallback(void*) = 0;
    virtual std::string getFullName() const = 0;
    virtual bool isTerminated() const = 0;
    virtual bool invokeMethod(std::string path, std::string method) = 0;
};
