#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include <QSignalSpy>

#include "presentnodesmodel.h"
#include "alljoynnode.h"

TEST(PresentNodesModel, doesInsertFoundNode)
{
    PresentNodesModel model;
    QSignalSpy spy(&model, SIGNAL(rowsInserted(QModelIndex,int,int)));

    std::shared_ptr<JoinedBusSession> session{nullptr};
    auto node = std::make_shared<AllJoynNode>(session, "/path");

    ASSERT_EQ(spy.length(), 0);
    EXPECT_EQ(model.rowCount(), 0);

    model.nodeFound(node);

    EXPECT_EQ(spy.length(), 1);
    EXPECT_EQ(model.rowCount(), 1);
}

