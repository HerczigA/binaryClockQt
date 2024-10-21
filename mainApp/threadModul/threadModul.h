#pragma once

#include <QList>
#include <QMap>
#include <QObject>
#include <QThread>
#include <QtGlobal>

#include <memory>
#include <typeindex>

class ThreadModul : public QObject 
{
    public:
        template<typename T, typename... Types>
        static std::shared_ptr<T> createComponentIntoNewThread(Types... args)
        {
            std::shared_ptr<QThread> thread;
            auto threadType = std::type_index(typeid(T));
            if (const auto it = s_threadMap.constFind(threadType); it != s_threadMap.constEnd()) 
            {
                thread = *it;
            }
            if (!thread) {
                thread = std::make_shared<QThread>();
                s_threadMap[threadType] = thread;
            }
            auto modul = std::make_shared<T>(args...);
            modul->moveToThread(thread.get());
            QObject::connect(thread.get(), &QThread::finished, modul.get(), &QObject::deleteLater, Qt::QueuedConnection);
            QObject::connect(thread.get(), &QThread::finished, thread.get(), &QThread::deleteLater, Qt::QueuedConnection);
            thread->start();
            return modul;
        }
        // clean up for sigsev
        static void cleanup() 
        {
            for (const auto it : s_threadMap.values()) {
                if (auto thread = it) {
                    thread->quit();
                    thread->wait();
                }
            }
            s_threadMap.clear();
        }

    private:
        ThreadModul() = delete;
        static QMap<std::type_index, std::shared_ptr<QThread>> s_threadMap;
};

QMap<std::type_index, std::shared_ptr<QThread>> ThreadModul::s_threadMap;
