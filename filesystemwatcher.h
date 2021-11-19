#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>
#include <QObject>
#include <QDebug>

class FileSystemWatcher : public QFileSystemWatcher
{
    Q_OBJECT
public:
    FileSystemWatcher();

public slots:
    void SomethingChanged(const QString &path);
    void SomeFilesChanged(const QString &path);
    void addUserPath(QString path);
    void removeUserPath(QString path);
};

#endif // FILESYSTEMWATCHER_H
