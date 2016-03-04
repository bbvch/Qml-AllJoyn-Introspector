#include <QMetaObject>
#include <QString>

#include <memory>

#include <alljoyn/BusAttachment.h>

#include "alljoynhelpers.h"
#include "introspectionlistener.h"
#include "introspectionthread.h"

IntrospectionThread::IntrospectionThread(QObject* parent) : QThread(parent)
{
}

void IntrospectionThread::run()
{
    AllJoynSession aj_session;
    AllJoynRouterSession aj_router_session;

    auto bus = std::make_shared<ajn::BusAttachment>("AllJoyn Introspector", true);

    AJ_CHECK(bus->Start());
    AJ_CHECK(bus->Connect());

    auto callback = [this] (std::shared_ptr<JoinedBusSession> session, std::string path, std::string xml)
    {
        QMetaObject::invokeMethod(
            this, "introspectionXmlReceived",
            Q_ARG(std::shared_ptr<JoinedBusSession>, session),
            Q_ARG(QString, QString(path.c_str())),
            Q_ARG(QString, QString(xml.c_str()))
        );
    };
    auto listener = std::make_shared<IntrospectionListener>(bus, callback);
    bus->RegisterAboutListener(*listener);

    // Ask for all About announcements
    AJ_CHECK(bus->WhoImplements(NULL));

    // Run Qt event loop
    exec();
}
