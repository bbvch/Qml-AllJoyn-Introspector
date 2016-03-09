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
void aj_check(const QStatus &status, const char* statement)
{
    if(ER_OK != status)
    {
        throw alljoyn_error(status, statement);
    }
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
