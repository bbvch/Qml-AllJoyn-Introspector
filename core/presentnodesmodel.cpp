#include "presentnodesmodel.h"

PresentNodesModel::PresentNodesModel(QObject* parent) : QAbstractListModel(parent)
{

}

void PresentNodesModel::nodeFound(std::shared_ptr<AllJoynNode> node)
{
    beginInsertRows(QModelIndex(), nodes.length(), nodes.length());
    nodes.append(node);
    endInsertRows();
}


int PresentNodesModel::rowCount(const QModelIndex &parent) const
{
    return nodes.length();
}

QVariant PresentNodesModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        auto& node = nodes.at(index.row());

        switch(role)
        {
        case int(UserRoles::Node):
        case Qt::DisplayRole:
            return {QMetaType::QObjectStar, node.get()};

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
    roleNames[int(UserRoles::Methods)] = "methods";

    return roleNames;
}
