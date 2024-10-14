#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

// class ListModel : public QOBject
// {
//     Q_OBJECT
//     Q_PROPERTY(QAbstractListModel* model READ model CONSTANT)
//     public:
//     ListModel(QObject* parent=nullptr)
//     {
//         mListModel = QSharedPointer<AbstractListModel<QObject*>>(new AbstractListModel<QVariant>(this));
//     }
//     QList<QObject*> model() const
//     {
//         return mListModel;
//     }
//     private:
//         QSharedPointer<AbstractListModel<QVariant>> mListModel;
// };

template<typename T>
class AbstractListModel : public QAbstractListModel
{
public:

    explicit AbstractListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}

    virtual int columnCount(const QModelIndex &parent) const override
    {
        if (parent.isValid())
            return 0;
        return 1;
    }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid() || index.row() >= mList.size())
            return QVariant();

        return QVariant::fromValue(mList.at(index.row()));
    }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        if (!hasIndex(row, column, parent))
            return QModelIndex();

        return createIndex(row, column);
    }

    virtual QModelIndex parent(const QModelIndex &index) const override
    {
        return QModelIndex();
    }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid())
            return 0;
        return mList.count();
    }

    void setList(const QList<T>& list)
    {
        beginResetModel();
        mList = list;
        endResetModel();
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (!index.isValid() || index.row() >= mList.size())
            return false;

        T item = value.value<T>();
        if (mList[index.row()] != item) {
            mList[index.row()] = item;
            emit dataChanged(index, index, {role});
            return true;
        }
        return false;
    }

    QList<T> getList() const
    {
        return mList;
    }

    Q_INVOKABLE void addNewElement(const QSharedPointer<T> element)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mList.append(element);
        endInsertRows();
    }
    
    Q_INVOKABLE void removeItem(int index) {
        if (index >= 0 && index < mList.size()) {
            beginRemoveRows(QModelIndex(), index, index);
            mList.removeAt(index);
            endRemoveRows();
        }
    }

    Q_INVOKABLE void updateItem(int index, const T& item) {
        if (index >= 0 && index < mList.size()) {
            mList[index] = item;
            QModelIndex modelIndex = createIndex(index, 0);
            emit dataChanged(modelIndex, modelIndex);
        }
    }

protected:
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[Qt::DisplayRole] = "display";
        return roles;
    }

private:
    QList<T> mList;
};