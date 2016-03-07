#pragma once

#include <memory>

#include <QXmlSimpleReader>
#include <QSharedPointer>

#include "joinedbussession_fw.h"

class AllJoynNode;


class IntrospectionParser : public QObject, public QXmlDefaultHandler
{
    Q_OBJECT

public:
    IntrospectionParser();

    bool startDocument() override;
    bool startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs) override;
    bool endElement(const QString &, const QString &, const QString &) override;
    bool fatalError(const QXmlParseException &exception) override;

signals:
    void nodeFound(std::shared_ptr<AllJoynNode>);

public slots:
    void introspectionXmlReceived(std::shared_ptr<JoinedBusSession> session, QString path, QString xml);

private:
    QXmlSimpleReader reader;
    std::shared_ptr<AllJoynNode> current_node;
    QString interface;
    QString method;
    QString params;
    QString returns;
};
