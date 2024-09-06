#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QObject>

template<typename T>
class ListModel : public QAbstractItemModel
{
    // Q_OBJECT
    public:
    ListModel(QObject *parent = nullptr)
    : QAbstractListModel(parent)
    {

    }
    virtual ~ListModel()
    {

    }
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {

    }
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {

    }
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {

    }
    virtual QModelIndex parent(const QModelIndex &index) const override
    {

    }
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {

    }
private:
    QList<T> mList;
};
