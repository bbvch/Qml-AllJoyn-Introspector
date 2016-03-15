#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include <QSignalSpy>

#include "methodsproxymodel.h"
#include "presentnodesmodel.h"
#include "alljoynnode.h"
#include "mockbussession.h"

TEST(PresentNodesModel, doesInsertFoundMethods)
{
    PresentNodesModel smodel;
    MethodsProxyModel model;

    model.setSourceModel(&smodel);
    QSignalSpy spy(&model, SIGNAL(rowsInserted(QModelIndex,int,int)));

    auto session = std::make_shared<MockBusSession>();
    auto node = std::make_shared<AllJoynNode>(session, "/path");

    node->addMethod("test", "echo", "s", "s");
    node->addMethod("test", "echo2", "s", "s");

    EXPECT_EQ(spy.length(), 0);

    smodel.nodeFound(node);

    ASSERT_EQ(spy.length(), 1);
    EXPECT_EQ(spy.at(0).at(0), QModelIndex{});
    EXPECT_EQ(spy.at(0).at(1).toUInt(), 0); // firstRow
    EXPECT_EQ(spy.at(0).at(2).toUInt(), 1); // lastRow
}

TEST(PresentNodesModel, withMultipleNodesAndMethods)
{
    PresentNodesModel smodel;
    MethodsProxyModel model;

    model.setSourceModel(&smodel);

    auto session = std::make_shared<MockBusSession>();

    auto node1 = std::make_shared<AllJoynNode>(session, "/path/1");
    node1->addMethod("test1", "0", "", "");
    node1->addMethod("test1", "1", "", "");
    smodel.nodeFound(node1);

    auto node2 = std::make_shared<AllJoynNode>(session, "/path/2");
    node2->addMethod("test2", "2", "", "");
    smodel.nodeFound(node2);

    auto node3 = std::make_shared<AllJoynNode>(session, "/path/3");
    smodel.nodeFound(node3);

    auto node4 = std::make_shared<AllJoynNode>(session, "/path/4");
    node4->addMethod("test4", "3", "", "");
    smodel.nodeFound(node4);

    auto node5 = std::make_shared<AllJoynNode>(session, "/path/5");
    smodel.nodeFound(node5);

    EXPECT_EQ(model.rowCount(), 4);
    EXPECT_EQ(model.data(model.index(0)).toString().toStdString(), "test1.0()");
    EXPECT_EQ(model.data(model.index(2)).toString().toStdString(), "test2.2()");
    EXPECT_EQ(model.data(model.index(3)).toString().toStdString(), "test4.3()");
}

TEST(PresentNodesModel, outOfBoundsAccessReturnsNull)
{
    PresentNodesModel smodel;
    MethodsProxyModel model;

    model.setSourceModel(&smodel);

    auto session = std::make_shared<MockBusSession>();

    auto node = std::make_shared<AllJoynNode>(session, "/path");
    smodel.nodeFound(node);

    EXPECT_EQ(model.rowCount(), 0);
    EXPECT_EQ(model.data(model.index(1)), QVariant{});
}

TEST(PresentNodesModel, methodsOnTerminatedSessionAreRemoved)
{
    PresentNodesModel smodel;
    MethodsProxyModel model;

    model.setSourceModel(&smodel);
    QSignalSpy spy(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)));

    auto session = std::make_shared<MockBusSession>();
    auto terminating_session = std::make_shared<MockBusSession>();

    auto node1 = std::make_shared<AllJoynNode>(session, "/path/1");
    node1->addMethod("test1", "1", "", "");
    smodel.nodeFound(node1);

    auto node2 = std::make_shared<AllJoynNode>(terminating_session, "/path/2");
    node2->addMethod("test2", "2", "", "");
    smodel.nodeFound(node2);

    auto node3 = std::make_shared<AllJoynNode>(session, "/path/3");
    node3->addMethod("test3", "3", "", "");
    smodel.nodeFound(node3);

    EXPECT_EQ(model.rowCount(), 3);

    terminating_session->terminated = true;
    terminating_session->callback("terminated");

    EXPECT_EQ(model.data(model.index(1)).toString().toStdString(), "test3.3()");

    ASSERT_EQ(spy.length(), 1);
    EXPECT_EQ(spy.at(0).at(0), QModelIndex{});
    EXPECT_EQ(spy.at(0).at(1).toInt(), 1); // firstRow
    EXPECT_EQ(spy.at(0).at(2).toInt(), 1); // lastRow
}
