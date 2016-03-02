#include <QMetaObject>
#include <QString>

#include <memory>

#include <alljoyn/BusAttachment.h>

#include "alljoynhelpers.h"
#include "introspectionlistener.h"
#include "introspectionthread.h"

QAllJoynBusSession::QAllJoynBusSession(std::shared_ptr<JoinedBusSession> session)
    : session{session}
{
}

QAllJoynBusSession::QAllJoynBusSession(QAllJoynBusSession const& other)
    : QObject(other.parent())
{
    session = other.session;
}

bool QAllJoynBusSession::invokeMethod(QString path, QString interface, QString method)
{
    std::cerr << "Not implemented: " << session->name() << ":" << session->port() << path.toStdString() << "/" << interface.toStdString() << "." << method.toStdString() << "()" << std::endl;
    return false;
}

void IntrospectionThread::run()
{
    qRegisterMetaType<QAllJoynBusSession>();

    AllJoynSession aj_session;
    AllJoynRouterSession aj_router_session;

    auto bus = std::make_shared<ajn::BusAttachment>("AllJoyn Introspector", true);

    AJ_CHECK(bus->Start());
    AJ_CHECK(bus->Connect());

    auto callback = [this] (std::shared_ptr<JoinedBusSession> session, std::string path, std::string xml)
    {
        auto qsession = QAllJoynBusSession{session};

        QMetaObject::invokeMethod(
                    this, "introspectionXmlReceived",
                    Q_ARG(QAllJoynBusSession, qsession),
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

void IntrospectionThread::introspectionXmlReceived(QAllJoynBusSession session, QString path, QString xml)
{
    std::cout << xml.toStdString() << std::endl;
}
