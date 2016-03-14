#include <iostream>

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
    session->addTerminationCallback(this, [wptr] (std::string reason)
    {
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

QVariant AllJoynNode::callInterfaceMethod(QString method, QList<QVariant> params)
{
    auto args = session->createArgs();
    for(auto& param : params)
    {
        if(param.type() == QVariant::Type::String)
        {
            args->addString(param.toString().toStdString());
        }
    }

    auto method_end = method.indexOf("(");
    auto method_name = method.left(method_end);

    auto ret = session->invokeMethod(path.toStdString(), method_name.toStdString(), std::move(args));

    auto len = ret->size();
    QList<QVariant> returns;

    for(size_t i=0; i<len; ++i)
    {
        QVariant value;

        try {
            auto s = ret->getString(i);
            value = QString::fromStdString(s.c_str());
        }
        catch(std::exception) {}

        returns.push_back(value);
    }

    return QVariant::fromValue(returns);
}

void AllJoynNode::emitSessionTerminated(std::string reason)
{
    emit sessionTerminated(QString::fromStdString(reason));
}

bool AllJoynNode::isAvailable() const
{
    return !session->isTerminated();
}
