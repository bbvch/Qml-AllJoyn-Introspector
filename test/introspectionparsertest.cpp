#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

#include "introspectionparser.h"
#include "alljoynnode.h"

auto typeRegistered = qRegisterMetaType<std::shared_ptr<JoinedBusSession>>();

TEST(IntrospectionParser, sendsNodeFound)
{
    IntrospectionParser parser;
    std::shared_ptr<JoinedBusSession> session{nullptr};

    QSignalSpy spy(&parser, SIGNAL(nodeFound(std::shared_ptr<AllJoynNode>)));

    ASSERT_EQ(spy.length(), 0);

    parser.introspectionXmlReceived(session, "/path", "<node></node>");

    EXPECT_EQ(spy.length(), 1);
}

TEST(IntrospectionParser, sendsNodeWithSimpleMethod)
{
    IntrospectionParser parser;
    std::shared_ptr<JoinedBusSession> session{nullptr};

    QSignalSpy spy(&parser, SIGNAL(nodeFound(std::shared_ptr<AllJoynNode>)));

    ASSERT_EQ(spy.length(), 0);

    parser.introspectionXmlReceived(session, "/path",
                                    "<node>"
                                        "<interface name=\"org.test\">"
                                            "<method name=\"run\"/>"
                                        "</interface>"
                                    "</node>");

    EXPECT_EQ(spy.length(), 1);

    auto args = spy.takeFirst();
    auto node = args.at(0).value<std::shared_ptr<AllJoynNode>>();

    EXPECT_EQ(node->getMethods().length(), 1);
    EXPECT_EQ(node->getMethods()[0].toStdString(), "org.test.run()");
}

TEST(IntrospectionParser, sendsNodeWithMethodWithParamsAndReturnValue)
{
    IntrospectionParser parser;
    std::shared_ptr<JoinedBusSession> session{nullptr};

    QSignalSpy spy(&parser, SIGNAL(nodeFound(std::shared_ptr<AllJoynNode>)));

    ASSERT_EQ(spy.length(), 0);

    parser.introspectionXmlReceived(session, "/path",
                                    "<node>"
                                        "<interface name=\"org.test\">"
                                            "<method name=\"itoa\">"
                                                "<arg direction=\"out\" type=\"s\"/>"
                                                "<arg direction=\"in\" type=\"i\" name=\"input\"/>"
                                            "</method>"
                                        "</interface>"
                                    "</node>"
                                    );

    EXPECT_EQ(spy.length(), 1);

    auto args = spy.takeFirst();
    auto node = args.at(0).value<std::shared_ptr<AllJoynNode>>();

    EXPECT_EQ(node->getMethods().length(), 1);
    EXPECT_EQ(node->getMethods()[0].toStdString(), "org.test.itoa(i):s");
}
