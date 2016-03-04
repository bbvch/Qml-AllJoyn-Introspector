#include <iostream>

#include "introspectionparser.h"
#include "alljoynnode.h"

IntrospectionParser::IntrospectionParser()
{

}

void IntrospectionParser::introspectionXmlReceived(std::shared_ptr<JoinedBusSession> session, QString path, QString xml)
{
    std::cout << xml.toStdString() << std::endl;
    emit nodeFound(std::make_shared<AllJoynNode>(session, path));
}
