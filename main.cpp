
#include <QGuiApplication>
#include <QScreen>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <mainApp/mainApp.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const auto width = app.primaryScreen()->size().width();
    const auto height = app.primaryScreen()->size().height();
    MainApp* mainApp = MainApp::getInstance(width, height, &app);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    qDebug() << "Current path:" << QDir::currentPath();
    qDebug() << "Trying to load:" << QUrl(QStringLiteral("qrc:/qml/main.qml")).toString();
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    // engine.rootContext()->setContextProperty("mainApp", mainApp);
    engine.load(url);


    return app.exec();
}
