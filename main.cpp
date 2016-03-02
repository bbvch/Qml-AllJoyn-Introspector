#include <QCoreApplication>

#include <memory>

#include <alljoyn/BusAttachment.h>

#include "alljoynhelpers.h"
#include "introspectionlistener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AllJoynSession aj_session;
    AllJoynRouterSession aj_router_session;

    auto bus = std::make_shared<ajn::BusAttachment>("AllJoyn Introspector", true);

    AJ_CHECK(bus->Start());
    AJ_CHECK(bus->Connect());

    auto listener = std::make_shared<IntrospectionListener>(bus);
    bus->RegisterAboutListener(*listener);

    // Ask for all About announcements
    AJ_CHECK(bus->WhoImplements(NULL));

    return a.exec();
}
