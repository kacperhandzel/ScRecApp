#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <QObject>
#include <QDateTime>
#include "EventItem.h"

class EventList : public QObject
{
    Q_OBJECT
public:
    explicit EventList(QObject *parent = nullptr);

    QVector<EventItem> items() const;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved();
    void postItemRemoved();

private:
    QVector<EventItem> mItems;

public slots:
    void appendItem(EventItem item);
    void clearList();

};

#endif // EVENTLIST_H
