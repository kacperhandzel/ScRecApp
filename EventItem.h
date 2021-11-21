#ifndef EVENTITEM_H
#define EVENTITEM_H

#endif // EVENTITEM_H

#include <QObject>
#include <QDateTime>
#pragma once
struct EventItem {
    QString fullPath;
    int eventType;
    bool isDir;
    QDateTime timestamp;

};

enum {
    CreatedEvent = 0,
    DeletedEvent,
    ModifiedEvent
};
