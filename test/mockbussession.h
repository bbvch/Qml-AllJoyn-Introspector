#pragma once

#include <memory>

#include "../ajintrospect/iobservablebussession.h"
#include "mockargumentlist.h"

class MockBusSession : public IObservableBusSession
{
public:
    CallbackType callback;
    bool terminated{false};

    void addTerminationCallback(void*, CallbackType callback) override
    {
        this->callback = callback;
    }

    void removeTerminationCallback(void*) override
    {
        this->callback = nullptr;
    }

    std::string getFullName() const override
    {
        return "MockSession";
    }

    bool isTerminated() const override
    {
        return terminated;
    }

    std::unique_ptr<ArgumentList> invokeMethod(std::string path, std::string method, std::unique_ptr<ArgumentList> args) override
    {
        return args;
    }

    std::unique_ptr<ArgumentList> createArgs() const override
    {
        return std::make_unique<MockArgumentList>();
    }

    std::string getStringProperty(std::string path, std::string property) const override
    {
        return "";
    }

    bool setStringProperty(std::string path, std::string property, std::string value) override
    {
        return false;
    }
};
