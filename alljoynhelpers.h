#pragma once

#include <string>
#include <exception>
#include <memory>
#include <iostream>

#include <alljoyn/Init.h>
#include <alljoyn/BusAttachment.h>

class alljoyn_error : public std::runtime_error
{
public:
    alljoyn_error(const QStatus &status, const char* statement);

private:
    static std::string make_what(const QStatus &status, const char* statement);
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
    AllJoynSession();

    std::shared_ptr<int> cleanup{};
};

struct AllJoynRouterSession
{
    AllJoynRouterSession();

    std::shared_ptr<int> cleanup{};
};

struct JoinedBusSession
{
public:
    JoinedBusSession(std::shared_ptr<ajn::BusAttachment> bus, const char* busName, ajn::SessionPort port, ajn::SessionOpts opts, std::shared_ptr<ajn::SessionListener> listener);

    ajn::SessionId id() const;

private:
    ajn::SessionId sessionId{};
    std::shared_ptr<ajn::BusAttachment> bus{};
    std::shared_ptr<ajn::SessionListener> sessionListener{};
    std::shared_ptr<int> cleanup{};
};
