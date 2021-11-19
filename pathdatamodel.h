#ifndef PATHDATAMODEL_H
#define PATHDATAMODEL_H

#include <QAbstractListModel>

class PathDataList;

class PathDataModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PathDataList *pathList READ list WRITE setList)

public:
    explicit PathDataModel(QObject *parent = nullptr);
    enum {
        DescriptionRole = Qt::UserRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PathDataList *list() const;
    void setList(PathDataList *list);

private:
    PathDataList *mList;
};

#endif // PATHDATAMODEL_H
