#pragma once

#include <QObject>
#include <QList>
#include <memory>
#include <QThread>
#include <QtGlobal>

class ThreadModul : public QObject 
{
    public:
        template<typename T, typename... Types>
        static std::shared_ptr<T> createComponentIntoNewThread(Types... args)
        {
            auto thread =  new QThread();
            auto modul = std::make_shared<T>(args...);
            modul->moveToThread(thread);
            QObject::connect(thread, &QThread::finished, modul.get(), &QObject::deleteLater);
            QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater, Qt::QueuedConnection);
            thread->start();
            return modul;
         }

    private:
        ThreadModul(QObject* parent = nullptr) : QObject(parent) {}
        ~ThreadModul() {
        }
};
