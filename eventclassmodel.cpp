#include "eventclassmodel.h"
#include "eventlist.h"

EventClassModel::EventClassModel(QObject *parent)
    : QAbstractTableModel(parent), mList(nullptr)
{
}

QVariant EventClassModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role==DisplayRole)
    {
        switch (section) {
        case (FilePathCol):
            return QString("Path");
        case (EventTypeCol):
            return QString("Event Type");
        case (isDirCol):
            return QString("Dir?");
        case (TimestampCol):
            return QString("Timestamp");
        }
    }
    return QVariant();
}

int EventClassModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

int EventClassModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant EventClassModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case DisplayRole:
    {
        const auto row = index.row();
        const auto item = mList->items().at(row);
        switch (index.column()) {
        case (FilePathCol):
            return item.fullPath;
        case (EventTypeCol):
        {
            switch (item.eventType) {
            case (CreatedEvent):
                return QString("Created");
            case (DeletedEvent):
                return QString("Deleted");
            case (ModifiedEvent):
                return QString("Modified");
            }
        }
        case (isDirCol):
            return item.isDir;
        case (TimestampCol):
            return item.timestamp.toString();

        }

        return QVariant();
    }
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> EventClassModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DisplayRole] = "display";
    return names;
}

EventList *EventClassModel::list() const
{
    return mList;
}

void EventClassModel::setList(EventList *list)
{
    beginResetModel();
    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList,&EventList::preItemAppended, this, [=] () {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList,&EventList::postItemAppended, this, [=] () {
            endInsertRows();
        });
        connect(mList,&EventList::preItemRemoved, this, [=] () {
            const int index = mList->items().size();
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mList,&EventList::postItemRemoved, this, [=] () {
            endRemoveRows();
        });
    }
    endResetModel();
}
