#pragma once

#include <QAbstractItemModel>
#include <QList>
#include <QObject>

template<typename T>
class MultiDimensionListModel : public QAbstractItemModel
{
    // Q_OBJECT
    // Q_PROPERTY()
    public:
    MultiDimensionListModel(QObject *parent = nullptr)
    : QAbstractItemModel(parent)
    {

    }
    virtual ~MultiDimensionListModel()
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
