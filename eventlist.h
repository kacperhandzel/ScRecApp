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

private:
    QVector<EventItem> mItems;

public slots:
    void appendItem(EventItem item);

};

#endif // EVENTLIST_H
