#pragma once

#include <string>
#include <functional>

#include "alljoynhelpers.h"

class QString;

constexpr const char* AJN_INTROSPECT_INTERFACE = "org.allseen.Introspectable";
constexpr const char* DBUS_INTROSPECT_INTERFACE = "org.freedesktop.DBus.Introspectable";

class IntrospectionListener : public ajn::AboutListener, public ajn::SessionListener, public std::enable_shared_from_this<IntrospectionListener>
{
public:
    using CallbackType = std::function<void(std::shared_ptr<JoinedBusSession> session, std::string path, std::string xml)>;
    IntrospectionListener(std::shared_ptr<ajn::BusAttachment> bus, CallbackType callback);

protected:
    void Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg) override;
    void SessionLost(ajn::SessionId sessionId, SessionLostReason reason) override;

private:
    std::shared_ptr<ajn::BusAttachment> bus;
    CallbackType callback;
};
