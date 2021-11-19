#ifndef PATHDATALIST_H
#define PATHDATALIST_H

#include <QObject>
#include <QVector>
#include <QFileInfo>
#include <QDir>
#include <QFileSystemWatcher>
struct PathDataItem
{
    int type;
    QString description;
};

class PathDataList : public QObject
{
    Q_OBJECT
public:
    explicit PathDataList(QObject *parent = nullptr);

    QVector<PathDataItem> items() const;
    bool addItem(PathDataItem item);

public slots:
    void appendItem(QString fullPath);
    void removeItem(int row);

signals:
    void preItemAppended();
    void postItemAppended();
    void itemAppended(QString fullPath); //do obslugi FileWatcherSys

    void preItemRemoved(int index);
    void postItemRemoved();
    void itemRemoved(QString fullPath); //do obslugi FileWatcherSys

private:
    QVector<PathDataItem> mItems;

};

#endif // PATHDATALIST_H
