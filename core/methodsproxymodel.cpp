#include "methodsproxymodel.h"
#include "presentnodesmodel.h"


MethodsProxyModel::MethodsProxyModel(QObject* parent)
{

}

void MethodsProxyModel::setSourceModel(PresentNodesModel* sourceModel)
{
    if(this->sourceModel)
    {
        QObject::disconnect(this->sourceModel, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)), this, SLOT(onRowsAboutToBeInserted(QModelIndex,int,int)));
        QObject::disconnect(this->sourceModel, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(onRowsInserted(QModelIndex,int,int)));
        QObject::disconnect(this->sourceModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
        QObject::disconnect(this->sourceModel, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(onRowsRemoved(QModelIndex,int,int)));
    }

    this->sourceModel = sourceModel;

    if(this->sourceModel)
    {
        QObject::connect(sourceModel, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)), this, SLOT(onRowsAboutToBeInserted(QModelIndex,int,int)));
        QObject::connect(sourceModel, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(onRowsInserted(QModelIndex,int,int)));
        QObject::connect(sourceModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
        QObject::connect(sourceModel, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(onRowsRemoved(QModelIndex,int,int)));
    }
}

QVariant MethodsProxyModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        int row = index.row();
        int srow = 0;
        int last_row{getMethodCount(0)};
        int first_row{0};

        while(last_row <= row && srow < sourceModel->rowCount() - 1)
        {
            first_row += getMethodCount(srow);
            ++srow;
            last_row += getMethodCount(srow);
        }

        if(last_row <= row)
        {
            return QVariant{};
        }

        auto offset = row - first_row;

        Q_ASSERT(offset >= 0 && offset < getMethodCount(srow));

        auto sindex = sourceModel->index(srow);
        auto node = qobject_cast<AllJoynNode*>(sourceModel->data(sindex, int(PresentNodesModel::UserRoles::Node)).value<QObject*>());
        Q_ASSERT(node);


        switch(role)
        {
        case int(UserRoles::NodeName):
            return QVariant::fromValue(node->getName());

        case int(UserRoles::Node):
            return QVariant::fromValue(node);

        case Qt::DisplayRole:
            return QVariant::fromValue(node->getMethods().at(offset));

        case int(UserRoles::Namespace):
        {
            auto nsEnd = node->getName().lastIndexOf(".");
            return QVariant::fromValue(node->getName().left(nsEnd));
        }

        default:
            return QVariant{};
        }
    }

    return QVariant{};
}

QHash<int, QByteArray> MethodsProxyModel::roleNames() const
{
    auto roleNames = QAbstractItemModel::roleNames();
    roleNames[int(UserRoles::NodeName)] = "nodeName";
    roleNames[int(UserRoles::Node)] = "node";
    roleNames[int(UserRoles::Namespace)] = "namespace";

    return roleNames;
}

QModelIndex MethodsProxyModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column);
}

QModelIndex MethodsProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex{};
}

int MethodsProxyModel::rowCount(const QModelIndex &parent) const
{
    if(sourceModel && parent != QModelIndex{})
        return 0;

    size_t sum{0};

    for(int i{0}; i < sourceModel->rowCount(); ++i)
    {
        sum += getMethodCount(i);
    }

    return sum;
}

int MethodsProxyModel::columnCount(const QModelIndex &) const
{
    return 1;
}

void MethodsProxyModel::onRowsAboutToBeInserted(QModelIndex sparent, int sfirst, int slast)
{
}

void MethodsProxyModel::onRowsInserted(QModelIndex, int sfirst, int slast)
{
    auto first = getFirstIndexOf(sfirst);
    auto last = getLastIndexOf(slast);

    beginInsertRows(QModelIndex{}, first, last);

    endInsertRows();
}

void MethodsProxyModel::onRowsAboutToBeRemoved(QModelIndex sparent, int sfirst, int slast)
{
    auto first = getFirstIndexOf(sfirst);
    auto last = getLastIndexOf(slast);

    beginRemoveRows(QModelIndex{}, first, last);
}

void MethodsProxyModel::onRowsRemoved(QModelIndex sparent, int sfirst, int slast)
{
    endRemoveRows();
}

int MethodsProxyModel::getMethodCount(int srow) const
{
    auto index = sourceModel->index(srow);
    auto node = qobject_cast<AllJoynNode*>(sourceModel->data(index, int(PresentNodesModel::UserRoles::Node)).value<QObject*>());
    Q_ASSERT(node);

    return node->getMethods().length();
}

int MethodsProxyModel::getFirstIndexOf(int srow) const
{
    int firstRow{0};

    for(int i{0}; i < srow; ++i)
    {
        firstRow += getMethodCount(i);
    }

    return firstRow;
}

int MethodsProxyModel::getLastIndexOf(int srow) const
{
    int lastRow{0};

    for(int i{0}; i <= srow; ++i)
    {
        lastRow += getMethodCount(i);
    }

    return lastRow - 1;
}
