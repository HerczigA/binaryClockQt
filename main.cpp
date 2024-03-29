#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>
#include <binaryClock.h>
#include <mainApp.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const auto width = app.primaryScreen()->size().width();
    const auto height = app.primaryScreen()->size().height();
    unique_ptr<MainApp>mainApp = make_unique<MainApp>(width, height);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("mainApp", mainApp.get());
    engine.load(url);


    return app.exec();
}
