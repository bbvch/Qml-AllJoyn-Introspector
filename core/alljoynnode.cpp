#include "alljoynnode.h"

Q_DECLARE_METATYPE(std::shared_ptr<JoinedBusSession>)

namespace {
    auto registered1 = qRegisterMetaType<std::shared_ptr<AllJoynNode>>();
    auto registered2 = qRegisterMetaType<std::shared_ptr<JoinedBusSession>>();
}

AllJoynNode::AllJoynNode(std::shared_ptr<JoinedBusSession> session, QString path, QObject *parent)
    : QObject(parent), session(session), path(path)
{
}

void AllJoynNode::addMethod(QString interface, QString method, QString params, QString returns)
{
    QString m = interface + "." + method + "(" + params + ":" + returns + ")";
    methods += m;
}

QList<QString> AllJoynNode::getMethods() const
{
    return methods;
}


