#include "pathdatamodel.h"
#include "pathdatalist.h"

PathDataModel::PathDataModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int PathDataModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}


QVariant PathDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const PathDataItem item = mList->items().at(index.row());
    switch (role) {
    case DescriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool PathDataModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool PathDataModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

QHash<int, QByteArray> PathDataModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DescriptionRole] = "description";
    return names;
}

PathDataList *PathDataModel::list() const
{
    return mList;
}

void PathDataModel::setList(PathDataList *list)
{
    beginResetModel();
    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList,&PathDataList::preItemAppended, this, [=] () {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList,&PathDataList::postItemAppended, this, [=] () {
            endInsertRows();
        });

        connect(mList,&PathDataList::preItemRemoved, this, [=] (int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mList,&PathDataList::postItemRemoved, this, [=] () {
            endRemoveRows();
        });
    }
    endResetModel();
}
