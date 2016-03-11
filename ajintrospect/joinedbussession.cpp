#include <sstream>

#include "joinedbussession.h"
#include "ajargumentlist.h"


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

std::unique_ptr<ArgumentList> JoinedBusSession::createArgs() const
{
    return std::make_unique<AjArgumentList>();
}

std::unique_ptr<ArgumentList> JoinedBusSession::invokeMethod(std::string path, std::string method, std::unique_ptr<ArgumentList> args)
{
    ajn::ProxyBusObject proxy(*sessionBus, busName.c_str(), path.c_str(), sessionId);
    ajn::Message reply(*sessionBus);

    auto interface_end = method.find_last_of('.');
    auto interface = method.substr(0, interface_end);
    auto method_name = method.substr(interface_end+1);

    auto args2 = dynamic_cast<AjArgumentList*>(args.get());

    try
    {
        AJ_CHECK(proxy.AddInterface(interface.c_str()));
        if(args2)
        {
            AJ_CHECK(proxy.MethodCall(interface.c_str(), method_name.c_str(), args2->data(), args2->size(), reply, 5000));
        }
        else
        {
            AJ_CHECK(proxy.MethodCall(interface.c_str(), method_name.c_str(), nullptr, 0, reply, 5000));
        }
    }
    catch(alljoyn_error& e)
    {
        std::cerr << e.what() << std::endl;
        return std::make_unique<AjArgumentList>();
    }

    return AjArgumentList::fromMessage(reply);
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

