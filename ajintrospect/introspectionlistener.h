#pragma once

#include <string>
#include <functional>

#include "alljoynhelpers.h"


class QString;
class IObservableBusSession;

constexpr const char* AJN_INTROSPECT_INTERFACE = "org.allseen.Introspectable";
constexpr const char* DBUS_INTROSPECT_INTERFACE = "org.freedesktop.DBus.Introspectable";

class IntrospectionListener : public ajn::AboutListener, public std::enable_shared_from_this<IntrospectionListener>
{
public:
    using CallbackType = std::function<void(std::shared_ptr<IObservableBusSession> session, std::string path, std::string xml)>;
    IntrospectionListener(std::shared_ptr<ajn::BusAttachment> bus, CallbackType callback);

protected:
    void Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg) override;

private:
    std::shared_ptr<ajn::BusAttachment> bus;
    CallbackType callback;
};
