#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include <QSignalSpy>

#include "presentnodesmodel.h"
#include "alljoynnode.h"
#include "mockbussession.h"

TEST(PresentNodesModel, doesInsertFoundNode)
{
    PresentNodesModel model;
    QSignalSpy spy(&model, SIGNAL(rowsInserted(QModelIndex,int,int)));

    auto session = std::make_shared<MockBusSession>();
    auto node = std::make_shared<AllJoynNode>(session, "/path");

    ASSERT_EQ(spy.length(), 0);
    EXPECT_EQ(model.rowCount(), 0);

    model.nodeFound(node);

    EXPECT_EQ(spy.length(), 1);
    EXPECT_EQ(model.rowCount(), 1);
}

TEST(PresentNodesModel, doesRemoveNodeWithTerminatedSession)
{
    PresentNodesModel model;
    QSignalSpy spy(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)));

    auto session = std::make_shared<MockBusSession>();
    auto node = std::make_shared<AllJoynNode>(session, "/path");

    model.nodeFound(node);

    EXPECT_EQ(spy.length(), 0);
    EXPECT_EQ(model.rowCount(), 1);

    session->callback("unexpected termination");

    EXPECT_EQ(spy.length(), 1);
    EXPECT_EQ(model.rowCount(), 0);
}
