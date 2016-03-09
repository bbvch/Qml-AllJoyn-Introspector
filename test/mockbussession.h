#pragma once

#include "../ajintrospect/iobservablebussession.h"

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
};
