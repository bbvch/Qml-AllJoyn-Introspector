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
    return session->getFullName().c_str() + path;
}

void AllJoynNode::callInterfaceMethod(QString method, QList<QVariant> params)
{
    // TODO use params

    auto method_end = method.indexOf("(");
    auto method_name = method.left(method_end);

    session->invokeMethod(path.toStdString(), method_name.toStdString());
}

void AllJoynNode::emitSessionTerminated(std::string reason)
{
    emit sessionTerminated(QString(reason.c_str()));
}

bool AllJoynNode::isAvailable() const
{
    return !session->isTerminated();
}
