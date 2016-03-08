#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QVariant>

#include "alljoynnode.h"


class PresentNodesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PresentNodesModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    enum class UserRoles
    {
        Node = Qt::UserRole + 1,
        Name,
        Methods
    };

signals:

public slots:
    void nodeFound(std::shared_ptr<AllJoynNode>);

private:
    QList<std::shared_ptr<AllJoynNode>> nodes;
};
