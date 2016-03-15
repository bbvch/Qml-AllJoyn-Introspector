#pragma once

#include <QAbstractItemModel>

class PresentNodesModel;


class MethodsProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    MethodsProxyModel(QObject* parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex{}) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    QHash<int, QByteArray> roleNames() const override;

    enum class UserRoles
    {
        NodeName = Qt::UserRole + 1,
        Node,
        Namespace
    };

    void setSourceModel(PresentNodesModel* sourceModel);

private slots:
    void onRowsAboutToBeInserted(QModelIndex sparent, int sfirst, int slast);
    void onRowsInserted(QModelIndex sparent, int sfirst, int slast);
    void onRowsAboutToBeRemoved(QModelIndex sparent, int sfirst, int slast);
    void onRowsRemoved(QModelIndex sparent, int sfirst, int slast);

private:
    int getFirstIndexOf(int srow) const;
    int getLastIndexOf(int srow) const;
    int getMethodCount(int srow) const;
    QModelIndex getSourceIndex(int srow) const;

    PresentNodesModel* sourceModel{nullptr};
};
