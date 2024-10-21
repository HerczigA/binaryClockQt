#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

#include <type_traits>

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

        return QVariant::fromValue(mList.at(index.row()).data());
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

    void setList(const QList<QSharedPointer<QObject>> list)
    {
        beginResetModel();
        mList = list;
        endResetModel();
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (!index.isValid() || index.row() >= mList.size())
            return false;

        QSharedPointer<QObject> item = qvariant_cast<QSharedPointer<QObject>>(value);
        if (mList[index.row()] != item)
        {
            mList[index.row()] = item;
            emit dataChanged(index, index, {role});
            return true;
        }
        return false;
    }

    QList<QSharedPointer<QObject>> getList() const
    {
        return mList;
    }

    Q_INVOKABLE void append(const QSharedPointer<QObject> element)
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

    Q_INVOKABLE void updateItem(int index, QSharedPointer<QObject> item) {
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

protected:
    QList<QSharedPointer<QObject>> mList;
};

template<typename T>
class ListModel : public AbstractListModel
{

public:
    ListModel(QObject* parent = nullptr) : AbstractListModel(parent) {}
    void append(const QSharedPointer<T>& item)
    {
        static_assert(std::is_base_of<QObject, T>::value, "T must inherit from QObject");
        AbstractListModel::append(item);
    }
};
