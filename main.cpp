#include <QCoreApplication>

#include <memory>
#include <thread>
#include <chrono>
#include <exception>
#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <string>

#include <alljoyn/AboutListener.h>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/AboutProxy.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/Session.h>
#include <alljoyn/SessionListener.h>

using namespace std::literals::chrono_literals;

class alljoyn_error : public std::runtime_error
{
public:
    alljoyn_error(const QStatus &status, const char* statement)
        : runtime_error{make_what(status, statement)}
    {
    }

private:
    static std::string make_what(const QStatus &status, const char* statement)
    {
        std::ostringstream what;
        what << "AllJoyn error in statement \"" << statement << "\": " << QCC_StatusText(status);
        return what.str();
    }
};

namespace {
const QStatus& aj_check(const QStatus &status, const char* statement)
{
    if(ER_OK != status)
    {
        throw alljoyn_error(status, statement);
    }
    return status;
}

#define AJ_CHECK(x) aj_check((x), #x)
}

struct AllJoynSession
{
    AllJoynSession()
    {
        AJ_CHECK(AllJoynInit());
        cleanup = std::shared_ptr<int>{nullptr, [](int*){ AllJoynShutdown(); }};
    }

    std::shared_ptr<int> cleanup{};
};

struct AllJoynRouterSession
{
    AllJoynRouterSession()
    {
        AJ_CHECK(AllJoynRouterInit());
        cleanup = std::shared_ptr<int>{nullptr, [](int*){ AllJoynRouterShutdown(); }};
    }

    std::shared_ptr<int> cleanup;
};

struct JoinedBusSession
{
public:
    JoinedBusSession(std::shared_ptr<ajn::BusAttachment> bus, const char* busName, ajn::SessionPort port, ajn::SessionOpts opts, std::shared_ptr<ajn::SessionListener> listener)
        : bus(bus), sessionListener(listener)
    {
        bus->EnableConcurrentCallbacks();
        AJ_CHECK(bus->JoinSession(busName, port, sessionListener.get(), sessionId, opts));
    }

    ajn::SessionId id() const
    {
        return sessionId;
    }

private:
    ajn::SessionId sessionId;
    std::shared_ptr<ajn::BusAttachment> bus;
    std::shared_ptr<ajn::SessionListener> sessionListener;
    std::shared_ptr<int> cleanup{ nullptr, [this](int*) { bus->LeaveJoinedSession(sessionId); sessionId = 0; } };
};

constexpr const char* AJN_INTROSPECT_INTERFACE = "org.allseen.Introspectable";
constexpr const char* DBUS_INTROSPECT_INTERFACE = "org.freedesktop.DBus.Introspectable";

class MyAboutListener : public ajn::AboutListener, public ajn::SessionListener, public std::enable_shared_from_this<MyAboutListener>
{
public:
    MyAboutListener(std::shared_ptr<ajn::BusAttachment> bus)
        : bus(bus)
    {
    }

protected:
    void Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg) override
    {
        QCC_UNUSED(version);
        QCC_UNUSED(aboutDataArg);

        ajn::AboutObjectDescription desc(objectDescriptionArg);
        auto numPaths = desc.GetPaths(NULL, 0);
        std::vector<const char*> paths(numPaths);
        desc.GetPaths(paths.data(), numPaths);

        JoinedBusSession session(bus, busName, port, {ajn::SessionOpts::TRAFFIC_MESSAGES, false, ajn::SessionOpts::PROXIMITY_ANY, ajn::TRANSPORT_ANY}, shared_from_this());

        for(auto path : paths)
        {
            std::cout << busName << ", " << port << ", " <<  path << std::endl;

            ajn::ProxyBusObject proxy(*bus, busName, path, session.id());
            ajn::Message reply(*bus);

            try
            {
                AJ_CHECK(proxy.AddInterface(AJN_INTROSPECT_INTERFACE));
                ajn::MsgArg params[] { { "s", "" } };

                AJ_CHECK(proxy.MethodCall(AJN_INTROSPECT_INTERFACE, "IntrospectWithDescription", params, 1, reply, 5000));
            }
            catch(alljoyn_error&)
            {
                try
                {
                    AJ_CHECK(proxy.AddInterface(DBUS_INTROSPECT_INTERFACE));
                    AJ_CHECK(proxy.MethodCall(DBUS_INTROSPECT_INTERFACE, "Introspect", nullptr, 0, reply, 5000));
                }
                catch(alljoyn_error& e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            if(reply->GetArg())
            {
                std::cout << reply->GetArg()->v_string.str << std::endl;
            }
        }
    }

    void SessionLost(ajn::SessionId sessionId, SessionLostReason reason) override
    {
        QCC_UNUSED(reason);

        std::cout << "Session " << sessionId << " terminated unexpectedly." << std::endl;
    }

private:
    std::shared_ptr<ajn::BusAttachment> bus;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AllJoynSession aj_session;
    AllJoynRouterSession aj_router_session;

    auto bus = std::make_shared<ajn::BusAttachment>("AllJoyn Introspector", true);

    AJ_CHECK(bus->Start());

    AJ_CHECK(bus->Connect());

    auto aboutListener = std::make_shared<MyAboutListener>(bus);
    bus->RegisterAboutListener(*aboutListener);

    // Ask for all About announcements
    AJ_CHECK(bus->WhoImplements(NULL));

    return a.exec();
}
