#pragma once

#include <QObject>
#include <QList>
#include <QVariant>

#include <memory>

#include "joinedbussession_fw.h"


class AllJoynNode : public QObject, public std::enable_shared_from_this<AllJoynNode>
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> methods READ getMethods)
    Q_PROPERTY(QString name READ getName)

public:
    AllJoynNode(std::shared_ptr<IObservableBusSession> session, QString path, QObject *parent = 0);
    virtual ~AllJoynNode();

    void addMethod(QString interface, QString method, QString params, QString returns);
    QList<QString> getMethods() const;
    QString getName() const;
    bool isAvailable() const;
    void notifyOnSessionTermination(); //< register with session to emit sessionTerminated signal

signals:
    void sessionTerminated(QString);

public slots:
    void callInterfaceMethod(QString,QList<QVariant>);

private:
    void emitSessionTerminated(std::string reason);

    std::shared_ptr<IObservableBusSession> session;
    QString path;

    QList<QString> methods;
};

Q_DECLARE_METATYPE(std::shared_ptr<AllJoynNode>)
