#include "DateHelper.h"

DateHelper::DateHelper(QObject *parent)
    : QObject(parent), m_date(QDate::currentDate())
{
}

QDate DateHelper::date() const
{
    return m_date;// "yyyy/MM/dd");
}

void DateHelper::setDate(const QDate &date)
{
    if (m_date != date) {
        m_date = date;
        emit dateChanged();
    }
}

void DateHelper::updateDate()
{
    setDate(QDate::currentDate());
}