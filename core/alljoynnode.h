#pragma once

#include <QObject>
#include <QVector>
#include <QVariant>
#include <QVariantMap>
#include <QStringList>

#include <memory>

#include "joinedbussession_fw.h"


class AllJoynNode : public QObject, public std::enable_shared_from_this<AllJoynNode>
{
    Q_OBJECT
    Q_PROPERTY(QStringList methods READ getMethods CONSTANT)
    Q_PROPERTY(QVariantMap properties READ getProperties CONSTANT)
    Q_PROPERTY(QStringList propertyNames READ getPropertyNames CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)

public:
    AllJoynNode(std::shared_ptr<IObservableBusSession> session, QString path, QObject *parent = 0);
    virtual ~AllJoynNode();

    void addMethod(QString interface, QString method, QString params, QString returns);
    void addProperty(QString interface, QString property, QString type);
    QStringList getMethods() const;
    QVariantMap getProperties() const;
    QStringList getPropertyNames() const;
    QString getName() const;
    bool isAvailable() const;
    void notifyOnSessionTermination(); //< register with session to emit sessionTerminated signal

signals:
    void sessionTerminated(QString);

public:
    Q_INVOKABLE QVariant callInterfaceMethod(QString,QList<QVariant>);

private:
    void emitSessionTerminated(std::string reason);

    std::shared_ptr<IObservableBusSession> session;
    QString path;

    QStringList methods;
    QVariantMap properties;
};

Q_DECLARE_METATYPE(std::shared_ptr<AllJoynNode>)
