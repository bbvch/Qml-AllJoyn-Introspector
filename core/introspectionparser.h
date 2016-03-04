#pragma once

#include <memory>

#include <QXmlSimpleReader>
#include <QSharedPointer>

class AllJoynNode;
class JoinedBusSession;


class IntrospectionParser : public QObject
{
    Q_OBJECT

public:
    IntrospectionParser();

signals:
    void nodeFound(std::shared_ptr<AllJoynNode>);

public slots:
    void introspectionXmlReceived(std::shared_ptr<JoinedBusSession> session, QString path, QString xml);

private:
    QXmlSimpleReader reader;
};
