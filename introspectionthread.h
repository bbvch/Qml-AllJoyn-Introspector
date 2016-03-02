#pragma once

#include <memory>

#include <QThread>
#include <QString>
#include <QObject>

class JoinedBusSession;

class QAllJoynBusSession : public QObject
{
    Q_OBJECT

public:
    QAllJoynBusSession() = default;
    explicit QAllJoynBusSession(std::shared_ptr<JoinedBusSession> session);
    QAllJoynBusSession(QAllJoynBusSession const& other);

    Q_INVOKABLE bool invokeMethod(QString path, QString interface, QString method);

signals:
    void sessionTerminated(); // TODO

private:
    std::shared_ptr<JoinedBusSession> session;
};

Q_DECLARE_METATYPE(QAllJoynBusSession)

class IntrospectionThread : public QThread
{
    Q_OBJECT

public slots:
    void introspectionXmlReceived(QAllJoynBusSession session, QString path, QString xml);

protected:
    void run() override;
};
