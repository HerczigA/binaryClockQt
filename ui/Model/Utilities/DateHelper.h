#pragma once

#include <QObject>
#include <QDate>

class DateHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date NOTIFY dateChanged)

public:
    explicit DateHelper(QObject *parent = nullptr);

    QDate date() const;
    void setDate(const QDate &date);

signals:
    void dateChanged();

public slots:
    void updateDate();

private:
    QDate m_date;
};
