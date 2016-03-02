#include "alljoynhelpers.h"

#include <sstream>

alljoyn_error::alljoyn_error(const QStatus &status, const char* statement)
    : runtime_error{make_what(status, statement)}
{
}

std::string alljoyn_error::make_what(const QStatus &status, const char* statement)
{
    std::ostringstream what;
    what << "AllJoyn error in statement \"" << statement << "\": " << QCC_StatusText(status);
    return what.str();
}

AllJoynSession::AllJoynSession()
{
    AJ_CHECK(AllJoynInit());
    cleanup = std::shared_ptr<int>{nullptr, [](int*){ AllJoynShutdown(); }};
}

AllJoynRouterSession::AllJoynRouterSession()
{
    AJ_CHECK(AllJoynRouterInit());
    cleanup = std::shared_ptr<int>{nullptr, [](int*){ AllJoynRouterShutdown(); }};
}

JoinedBusSession::JoinedBusSession(std::shared_ptr<ajn::BusAttachment> bus, const char* busName, ajn::SessionPort port, ajn::SessionOpts opts, std::shared_ptr<ajn::SessionListener> listener)
    : sessionBus(bus), busName(busName), sessionPort(port), sessionListener(listener)
{
    bus->EnableConcurrentCallbacks();
    AJ_CHECK(bus->JoinSession(busName, port, sessionListener.get(), sessionId, opts));
    cleanup = std::shared_ptr<int>{nullptr, [this](int*) { this->sessionBus->LeaveJoinedSession(sessionId); sessionId = 0; }};
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
