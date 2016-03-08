#pragma once

#include <QObject>
#include <QList>
#include <QVariant>

#include <memory>

#include "joinedbussession_fw.h"


class AllJoynNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> methods READ getMethods)
    Q_PROPERTY(QString name READ getName)

public:
    AllJoynNode(std::shared_ptr<JoinedBusSession> session, QString path, QObject *parent = 0);

public:
    void addMethod(QString interface, QString method, QString params, QString returns);
    QList<QString> getMethods() const;
    QString getName() const;

signals:
    void sessionTerminated();

public slots:
    void invokeMethod(QString,QList<QVariant>,QList<QVariant>&);

private:
    std::shared_ptr<JoinedBusSession> session;
    QString path;

    QList<QString> methods;
};

Q_DECLARE_METATYPE(std::shared_ptr<AllJoynNode>)
