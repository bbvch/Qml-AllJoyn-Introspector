#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

#include "introspectionparser.h"
#include "alljoynnode.h"

Q_DECLARE_METATYPE(std::shared_ptr<JoinedBusSession>)
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
