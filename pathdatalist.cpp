#include "pathdatalist.h"

PathDataList::PathDataList(QObject *parent) : QObject(parent)
{
    mItems.append({1,QString("Plik A")});
}

QVector<PathDataItem> PathDataList::items() const
{
    return mItems;
}

bool PathDataList::addItem(PathDataItem item)
{
    emit preItemAppended();
    this->mItems.append(item);
    emit postItemAppended();
    return true;
}

void PathDataList::appendItem(QString fullPath)
{
    PathDataItem item;
    QFileInfo file_info;
    fullPath.remove(0,7); //Usun file://
    file_info.setFile(fullPath);

    item.description = file_info.filePath();
    if (file_info.isFile())
        item.type = 1;
    if (file_info.isDir())
        item.type = 0;

    emit preItemAppended();
    this->mItems.append(item);
    emit postItemAppended();

}

void PathDataList::removeItem(int row)
{
    emit preItemRemoved(row);
    this->mItems.remove(row);
    emit postItemRemoved();
    return;
}
