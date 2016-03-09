#include <sstream>

#include "joinedbussession.h"


JoinedBusSession::JoinedBusSession(std::shared_ptr<ajn::BusAttachment> bus, const char* busName, ajn::SessionPort port, ajn::SessionOpts opts)
    : sessionBus(bus), busName(busName), sessionPort(port)
{
    bus->EnableConcurrentCallbacks();

    AJ_CHECK(bus->JoinSession(busName, port, this, sessionId, opts));
    cleanup = std::shared_ptr<int>{nullptr, [this](int*) { this->terminateSession("shutdown", false); }};
}


void JoinedBusSession::SessionLost(ajn::SessionId sessionId, SessionLostReason reason)
{
    QCC_UNUSED(reason);
    QCC_UNUSED(sessionId);

    terminateSession("unexpected event", true);
}

void JoinedBusSession::terminateSession(std::string reason, bool isError)
{
    if(!isTerminated())
    {
        if(!isError)
        {
            this->sessionBus->LeaveJoinedSession(sessionId);
        }

        sessionId = 0;

        for(auto cb : callbacks)
        {
            cb.second(reason);
        }
    }
}

void JoinedBusSession::addTerminationCallback(void* reference, CallbackType callback)
{
    callbacks[reference] = callback;
}

void JoinedBusSession::removeTerminationCallback(void *reference)
{
    callbacks.erase(reference);
}

std::string JoinedBusSession::getFullName() const
{
    std::stringstream s;
    s << name() << ":" << sessionPort;
    return s.str();
}

bool JoinedBusSession::isTerminated() const
{
    return sessionId == 0;
}

ajn::SessionId JoinedBusSession::id() const
{
    return sessionId;
}

std::string JoinedBusSession::name() const
{
    return busName;
}

ajn::SessionPort JoinedBusSession::port() const
{
    return sessionPort;
}

std::shared_ptr<ajn::BusAttachment> JoinedBusSession::bus() const
{
    return sessionBus;
}

