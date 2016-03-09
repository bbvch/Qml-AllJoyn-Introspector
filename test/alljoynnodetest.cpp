#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

#include "introspectionparser.h"
#include "alljoynnode.h"
#include "mockbussession.h"


TEST(AllJoynNode, notifiesOnSessionTermination)
{
    auto session = std::make_shared<MockBusSession>();
    auto ajn = std::make_shared<AllJoynNode>(session, "/path");

    ajn->notifyOnSessionTermination();
    QSignalSpy spy(ajn.get(), SIGNAL(sessionTerminated(QString)));

    ASSERT_EQ(spy.length(), 0);
    ASSERT_TRUE(ajn->isAvailable());

    session->callback("some reason");
    session->terminated = true;

    ASSERT_EQ(spy.length(), 1);
    ASSERT_EQ(spy.at(0).first().toString().toStdString(), "some reason");
    ASSERT_FALSE(ajn->isAvailable());
}

TEST(AllJoynNode, nodeDeletedBeforeSession)
{
    auto session = std::make_shared<MockBusSession>();
    auto ajn = std::make_shared<AllJoynNode>(session, "/path");

    ajn->notifyOnSessionTermination();
    QSignalSpy spy(ajn.get(), SIGNAL(sessionTerminated(QString)));

    ajn.reset();

    ASSERT_EQ(spy.length(), 0);
    ASSERT_FALSE(session->callback);
}

TEST(AllJoynNode, notifyCanBeCalledMultipleTimes)
{
    auto session = std::make_shared<MockBusSession>();
    auto ajn = std::make_shared<AllJoynNode>(session, "/path");

    ajn->notifyOnSessionTermination();
    ajn->notifyOnSessionTermination();
    ajn->notifyOnSessionTermination();

    QSignalSpy spy(ajn.get(), SIGNAL(sessionTerminated(QString)));

    session->callback("some reason");

    ASSERT_EQ(spy.length(), 1);
}

TEST(AllJoynNode, nodeDeletedWithoutRequestingNotification)
{
    auto session = std::make_shared<MockBusSession>();
    auto ajn = std::make_shared<AllJoynNode>(session, "/path");

    ajn.reset();
}
