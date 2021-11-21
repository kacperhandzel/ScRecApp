#ifndef EVENTCLASSMODEL_H
#define EVENTCLASSMODEL_H

#include <QAbstractTableModel>

class EventList;

class EventClassModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(EventList *eventList READ list WRITE setList);

public:
    explicit EventClassModel(QObject *parent = nullptr);

    enum {
        DisplayRole = Qt::DisplayRole
    };

    enum {
        FilePathCol = 0,
        EventTypeCol,
        isDirCol,
        TimestampCol
    };
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    EventList *list() const;
    void setList(EventList *list);

private:
    EventList *mList;
};

#endif // EVENTCLASSMODEL_H
