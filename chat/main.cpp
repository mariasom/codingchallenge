#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include "chatserver.h"

int main(int argc, char *argv[]) {

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    std::cout << "zacinam" << std::endl;
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChatServer>("chatserver.backend", 1, 0, "ChatServer");

    // QQmlApplicationEngine engine;
    // engine.load(QUrl::fromLocalFile("chat.qml"));
    // if (engine.rootObjects().isEmpty())
    //     return -1;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("chat.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    std::cout << "koncim" << std::endl;
    return app.exec();

}