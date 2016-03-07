#include <QCoreApplication>

#include "introspectionthread.h"
#include "introspectionparser.h"
#include "alljoynnode.h"
#include "joinedbussession_fw.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IntrospectionParser introspectionParser;
    IntrospectionThread introspectionThread;

    QObject::connect(&introspectionThread, SIGNAL(introspectionXmlReceived(std::shared_ptr<JoinedBusSession>,QString,QString)), &introspectionParser, SLOT(introspectionXmlReceived(std::shared_ptr<JoinedBusSession>,QString,QString)));

    introspectionThread.start();

    return a.exec();
}
