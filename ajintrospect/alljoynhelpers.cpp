#include "alljoynhelpers.h"

#include <sstream>

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
