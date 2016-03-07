#pragma once

#include <QString>
#include <QThread>

#include "../core/joinedbussession_fw.h"


class IntrospectionThread : public QThread
{
    Q_OBJECT

public:
    IntrospectionThread(QObject* parent = 0);

signals:
    void introspectionXmlReceived(std::shared_ptr<JoinedBusSession> session, QString path, QString xml);

protected:
    void run() override;
};
