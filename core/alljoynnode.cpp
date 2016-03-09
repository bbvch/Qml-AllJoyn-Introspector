#include "alljoynnode.h"

namespace {
    auto registered1 = qRegisterMetaType<std::shared_ptr<AllJoynNode>>();
    auto registered2 = qRegisterMetaType<std::shared_ptr<IObservableBusSession>>();
}

AllJoynNode::AllJoynNode(std::shared_ptr<IObservableBusSession> session, QString path, QObject *parent)
    : QObject(parent), session(session), path(path)
{
}

void AllJoynNode::notifyOnSessionTermination()
{
    auto wptr = std::weak_ptr<AllJoynNode>{shared_from_this()};
    session->addTerminationCallback(this, [wptr] (std::string reason) {
        if(auto ptr = wptr.lock())
        {
            ptr->emitSessionTerminated(reason);
        }
    });
}

AllJoynNode::~AllJoynNode()
{
    session->removeTerminationCallback(this);
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

void AllJoynNode::emitSessionTerminated(std::string reason)
{
    emit sessionTerminated(QString(reason.c_str()));
}

bool AllJoynNode::isAvailable() const
{
    return !session->isTerminated();
}
