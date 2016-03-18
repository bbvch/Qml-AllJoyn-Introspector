#include <algorithm>

#include "presentnodesmodel.h"

PresentNodesModel::PresentNodesModel(QObject* parent) : QAbstractListModel(parent)
{
}

void PresentNodesModel::nodeFound(std::shared_ptr<AllJoynNode> node)
{
    node->notifyOnSessionTermination();

    if(node->isAvailable())
    {
        beginInsertRows(QModelIndex(), nodes.length(), nodes.length());
        QObject::connect(node.get(), SIGNAL(sessionTerminated(QString)), this, SLOT(nodeLost(QString)));
        nodes.append(node);
        endInsertRows();
    }
}

void PresentNodesModel::nodeLost(QString reason)
{
    Q_UNUSED(reason);

    AllJoynNode* node = qobject_cast<AllJoynNode*>(sender());

    auto pos = std::find_if(nodes.begin(), nodes.end(), [node] (auto const& n) { return n.get() == node; });

    if(pos != nodes.end())
    {
        auto index = pos - nodes.begin();
        beginRemoveRows(QModelIndex(), index, index);
        nodes.erase(pos);
        endRemoveRows();
    }
}

int PresentNodesModel::rowCount(const QModelIndex &parent) const
{
    if(parent == QModelIndex())
    {
        return nodes.length();
    }
    else
    {
        return 0;
    }
}

QVariant PresentNodesModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        auto& node = nodes.at(index.row());

        switch(role)
        {
        case Qt::DisplayRole:
        case int(UserRoles::Name):
            return {node->getName()};

        case int(UserRoles::Node):
            return QVariant::fromValue<QObject*>(node.get());

        case int(UserRoles::Methods):
            return {node->getMethods()};
        }
    }

    return {};
}

QHash<int, QByteArray> PresentNodesModel::roleNames() const
{
    auto roleNames = QAbstractListModel::roleNames();
    roleNames[int(UserRoles::Node)] = "node";
    roleNames[int(UserRoles::Name)] = "name";
    roleNames[int(UserRoles::Methods)] = "methods";

    return roleNames;
}
