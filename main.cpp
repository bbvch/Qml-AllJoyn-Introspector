#include <QCoreApplication>

#include "introspectionthread.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IntrospectionThread introspectionThread;
    introspectionThread.start();

    return a.exec();
}
