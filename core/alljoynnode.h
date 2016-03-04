#pragma once

#include <QObject>
#include <QList>

#include <memory>

class JoinedBusSession;


class AllJoynNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> methods READ getMethods)

public:
    AllJoynNode(std::shared_ptr<JoinedBusSession> session, QString path, QObject *parent = 0);

public:
    void addMethod(QString interface, QString method, QString params, QString returns);
    QList<QString> getMethods() const;

signals:

public slots:

private:
    std::shared_ptr<JoinedBusSession> session;
    QString path;

    QList<QString> methods;
};

Q_DECLARE_METATYPE(std::shared_ptr<AllJoynNode>)
