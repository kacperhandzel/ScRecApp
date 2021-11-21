#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include "EventItem.h"


struct DirInternalItem {
    int dir_cnt = 0;
    int file_cnt = 0;
};

class FileSystemWatcher : public QFileSystemWatcher
{
    Q_OBJECT
public:
    FileSystemWatcher();

public slots:
    void SomethingChanged(const QString &path);

    void addUserPath(QString path);
    void removeUserPath(QString path);

private:
    //Dane do eventow
    bool insertDirMapItem(QString path, DirInternalItem dirIntItem); //
    bool removeDirMapItem(QString path);
    int countDirs(QString path);
    int countFiles(QString path);

    void prepareDirMapToInsert(QString path);

    QMap<QString, DirInternalItem> dirMap;

    //Porownanie katalogow po zmianie
    void compareDir(QString path);

    EventItem createItem(QString path, int eventType, bool isDir);

signals:
    void putEventItem(EventItem item);

};

#endif // FILESYSTEMWATCHER_H
