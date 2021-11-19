#include "filesystemwatcher.h"

FileSystemWatcher::FileSystemWatcher()
{
    connect(this,&FileSystemWatcher::directoryChanged, this, &FileSystemWatcher::SomethingChanged);
    connect(this,&FileSystemWatcher::fileChanged, this, &FileSystemWatcher::SomeFilesChanged);
}

void FileSystemWatcher::SomethingChanged(const QString &path)
{
    const QString t_path = path;
    qDebug() << t_path << "Changed";
}

void FileSystemWatcher::SomeFilesChanged(const QString &path)
{
    const QString t_path = path;
    qDebug() << t_path << " file Changed";
}

void FileSystemWatcher::addUserPath(QString path)
{
    this->addPath(path);
    qDebug() << path << " path added";
}

void FileSystemWatcher::removeUserPath(QString path)
{
    this->removePath(path);
    qDebug() << path << " path removed";
}
