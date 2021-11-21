#include "FileSystemWatcher.h"

FileSystemWatcher::FileSystemWatcher()
{
    connect(this,&FileSystemWatcher::directoryChanged, this, &FileSystemWatcher::SomethingChanged);
}

void FileSystemWatcher::SomethingChanged(const QString &path)
{
    const auto t_path = path;
    qDebug() << t_path << "Changed";
    this->compareDir(path);

}


void FileSystemWatcher::addUserPath(QString path)
{
    this->addPath(path);
    qDebug() << path << " path added";
    // Tworzenie DirIntItem
    this->prepareDirMapToInsert(path);

}

void FileSystemWatcher::removeUserPath(QString path)
{
    this->removeDirMapItem(path);
    this->removePath(path);
    qDebug() << path << " path removed";
}

void FileSystemWatcher::stopWatching()
{
    //disconnect(this,&FileSystemWatcher::directoryChanged, this, &FileSystemWatcher::SomethingChanged);
    this->isWatching = false;
}

void FileSystemWatcher::startWatching()
{
    //connect(this,&FileSystemWatcher::directoryChanged, this, &FileSystemWatcher::SomethingChanged);
    this->isWatching = true;
}

bool FileSystemWatcher::insertDirMapItem(QString path, DirInternalItem dirIntItem)
{
    this->dirMap.insert(path, dirIntItem);
    return true;
}

bool FileSystemWatcher::removeDirMapItem(QString path)
{
    this->dirMap.remove(path);
    return true;
}

int FileSystemWatcher::countDirs(QString path)
{
    QDir dir;
    dir.setFilter(QDir::Dirs);
    dir.setCurrent(path);

    auto dirDirs_cnt = dir.count(); //licznosc plikow w katalogu
    return dirDirs_cnt;
}

int FileSystemWatcher::countFiles(QString path)
{
    QStringList filters;
    filters << "*.*"; //Wyfiltrowanie plikow

    QDir dir;
    dir.setFilter(QDir::Files);
    dir.setCurrent(path);
    dir.setNameFilters(filters);

    auto dirFiles_cnt = dir.count(); //licznosc plikow w katalogu
    return dirFiles_cnt;
}

QStringList FileSystemWatcher::getDirList(QString path)
{
    QDir dir;
    dir.setFilter(QDir::Dirs);
    dir.setCurrent(path);
    return dir.entryList();
}

void FileSystemWatcher::prepareDirMapToInsert(QString path)
{
    DirInternalItem temp_item;

    temp_item.file_cnt = this->countFiles(path);
    temp_item.dir_cnt = this->countDirs(path);
    temp_item.dirList = this->getDirList(path);

    this->insertDirMapItem(path,temp_item);
}

void FileSystemWatcher::compareDir(QString path)
{
    auto actFileCnt = this->countFiles(path);
    auto actDirCnt = this->countDirs(path);
    auto actDirList = this->getDirList(path);

    auto& tempItem = this->dirMap[path];

    auto fileCntDiff = actFileCnt - tempItem.file_cnt;
    auto dirCntDiff = actDirCnt - tempItem.dir_cnt;

    if (fileCntDiff>0 || dirCntDiff > 0)
    {
        qDebug() << "Created";

        bool isDir = (fileCntDiff > 0 ? false : true);
        const auto item = createItem(path, CreatedEvent, isDir);
        if(isWatching)
            emit putEventItem(item);
    }
    else if (fileCntDiff < 0 || dirCntDiff < 0)
    {
        qDebug() << "Removed";

        bool isDir = (fileCntDiff < 0 ? false : true);
        const auto item = createItem(path, DeletedEvent, isDir);
        if(isWatching)
           emit putEventItem(item);
    }
    else if (fileCntDiff==0 && dirCntDiff == 0)
    {

        qDebug() << "Modified/Renamed";

        bool isDir = (this->compareDirList(tempItem.dirList,actDirList) ? true : false);
        const auto item = createItem(path, ModifiedEvent, isDir);
        if(isWatching)
            emit putEventItem(item);
    }
    tempItem.dir_cnt = actDirCnt;
    tempItem.file_cnt = actFileCnt;
    tempItem.dirList = actDirList;

}

bool FileSystemWatcher::compareDirList(QStringList oldDirList,QStringList newDirList)
{
    auto oldDirSet = QSet<QString>(oldDirList.begin(),oldDirList.end());
    auto newDirSet = QSet<QString>(newDirList.begin(),newDirList.end());

    const auto diffSet  = oldDirSet.subtract(newDirSet);
    if (diffSet.size()>0)
        return true;
    return false;

}

EventItem FileSystemWatcher::createItem(QString path, int eventType, bool isDir)
{
    EventItem item;
    item.fullPath = path;
    item.eventType = eventType;
    item.isDir = isDir;
    item.timestamp = QDateTime::currentDateTime();
    return item;
}

