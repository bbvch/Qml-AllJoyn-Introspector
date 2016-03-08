#include "alljoynnode.h"

namespace {
    auto registered1 = qRegisterMetaType<std::shared_ptr<AllJoynNode>>();
    auto registered2 = qRegisterMetaType<std::shared_ptr<JoinedBusSession>>();
}

AllJoynNode::AllJoynNode(std::shared_ptr<JoinedBusSession> session, QString path, QObject *parent)
    : QObject(parent), session(session), path(path)
{
    // TODO register callback for session termination
}

void AllJoynNode::addMethod(QString interface, QString method, QString params, QString returns)
{
    QString m = interface + "." + method + "(" + params + ")";
    if(returns.length() > 0)
    {
        m += ":" + returns;
    }

    methods += m;
}

QList<QString> AllJoynNode::getMethods() const
{
    return methods;
}

QString AllJoynNode::getName() const
{
    return path;
}

void AllJoynNode::invokeMethod(QString method, QList<QVariant> params, QList<QVariant>& returns)
{

}
