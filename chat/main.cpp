#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include "chatserver.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChatServer>("chatserver.backend", 1, 0, "ChatServer");

    ChatServer server;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("server", &server);
    engine.load(QUrl::fromLocalFile("chat.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
