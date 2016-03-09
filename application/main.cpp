#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "introspectionthread.h"
#include "introspectionparser.h"
#include "presentnodesmodel.h"
#include "alljoynnode.h"
#include "joinedbussession_fw.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /* Set organization information for persistent Settings */
    QCoreApplication::setOrganizationName("bbv Software Services AG");
    QCoreApplication::setOrganizationDomain("ch.bbv");
    QCoreApplication::setApplicationName("AllJoynIntrospector");

    IntrospectionParser introspectionParser;
    IntrospectionThread introspectionThread;

    /* Let parsing and lifecycle-management of sessions happen entirely in separate thread to avoid race conditions */
    introspectionParser.moveToThread(&introspectionThread);
    QObject::connect(&introspectionThread, SIGNAL(introspectionXmlReceived(std::shared_ptr<IObservableBusSession>,QString,QString)), &introspectionParser, SLOT(introspectionXmlReceived(std::shared_ptr<IObservableBusSession>,QString,QString)));

    PresentNodesModel presentNodes;
    QObject::connect(&introspectionParser, SIGNAL(nodeFound(std::shared_ptr<AllJoynNode>)), &presentNodes, SLOT(nodeFound(std::shared_ptr<AllJoynNode>)));

    QQmlApplicationEngine engine;

    auto ctxt = engine.rootContext();
    ctxt->setContextProperty("presentNodes", &presentNodes);

    engine.load(QUrl("qrc:/main.qml"));


    introspectionThread.start();
    return app.exec();
}
