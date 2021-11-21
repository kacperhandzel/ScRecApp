#include "eventlist.h"

EventList::EventList(QObject *parent) : QObject(parent)
{

}

QVector<EventItem> EventList::items() const
{
    return mItems;
}

void EventList::appendItem(EventItem item)
{
    emit preItemAppended();
    this->mItems.append(item);
    emit postItemAppended();
}

void EventList::clearList()
{
    emit preItemRemoved();
    this->mItems.clear();
    emit postItemRemoved();
}
