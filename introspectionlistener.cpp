#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <memory>

#include <alljoyn/AboutListener.h>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/AboutProxy.h>
#include <alljoyn/Session.h>
#include <alljoyn/SessionListener.h>

#include "alljoynhelpers.h"
#include "introspectionlistener.h"

IntrospectionListener::IntrospectionListener(std::shared_ptr<ajn::BusAttachment> bus)
    : bus(bus)
{
}

void IntrospectionListener::Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg)
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

void IntrospectionListener::SessionLost(ajn::SessionId sessionId, SessionLostReason reason)
{
    QCC_UNUSED(reason);

    std::cout << "Session " << sessionId << " terminated unexpectedly." << std::endl;
}

