#include <iostream>

#include "introspectionparser.h"
#include "alljoynnode.h"

IntrospectionParser::IntrospectionParser()
{
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
}

void IntrospectionParser::introspectionXmlReceived(std::shared_ptr<JoinedBusSession> session, QString path, QString xml)
{
    current_node = std::make_shared<AllJoynNode>(session, path);

    QXmlInputSource input;
    input.setData(xml);

    reader.parse(input);

    if(current_node)
    {
        emit nodeFound(std::move(current_node));
    }
}

bool IntrospectionParser::startDocument()
{
    interface = "";
    method = "";
    params = "";
    returns = "";

    return true;
}

bool IntrospectionParser::startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs)
{
    if(name == "interface")
    {
        interface = attrs.value("name");
    }
    else if(name == "method")
    {
        method = attrs.value("name");
    }
    else if(name == "arg")
    {
        auto direction = attrs.value("direction");
        auto type = attrs.value("type");

        if(direction == "out")
        {
            returns += type;
        }
        else
        {
            params += type;
        }
    }

    return true;
}

bool IntrospectionParser::endElement(const QString &, const QString &, const QString &name)
{
    if(name == "interface")
    {
        interface = "";
    }
    else if(name == "method")
    {
        current_node->addMethod(interface, method, params, returns);

        method = "";
        params = "";
        returns = "";
    }

    return true;
}

bool IntrospectionParser::fatalError(const QXmlParseException &exception)
{
    std::cerr << exception.message().toStdString() << std::endl;

    current_node = nullptr;

    return false;
}
