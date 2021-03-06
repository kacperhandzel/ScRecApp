#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QSet>
#include "EventItem.h"


struct DirInternalItem {
    int dir_cnt {0};
    int file_cnt {0};
    QStringList dirList {};
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

    void stopWatching();
    void startWatching();

private:
    //Dane do eventow

    bool insertDirMapItem(QString path, DirInternalItem dirIntItem); //
    bool removeDirMapItem(QString path);
    int countDirs(QString path);
    int countFiles(QString path);
    QStringList getDirList(QString path); //pobiera liste katalogow wewnatrz path

    void prepareDirMapToInsert(QString path);

    //Porownanie katalogow po zmianie
    void compareDir(QString path);
    bool compareDirList(QStringList oldDirList, QStringList newDirList);

    EventItem createItem(QString path, int eventType, bool isDir);

    QMap<QString, DirInternalItem> dirMap;
    bool isWatching = true;



signals:
    void putEventItem(EventItem item);

};

#endif // FILESYSTEMWATCHER_H
