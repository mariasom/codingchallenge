#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <string>
#include <map>
#include <iostream>

struct client {
    std::string userID;
    std::string username;
};

class ChatServer: public QObject {
    Q_OBJECT

    // Q_PROPERTY(client id READ id WRITE setID NOTIFY register);

    // Q_PROPERTY();
    // Q_PROPERTIES();

    // Q_INVOCABLE register();
    // Q_INVOCABLE sendMessage();

 signals:
        // void update(client c, std::string from, std::string);

 public:
    explicit ChatServer(QObject *parent = nullptr);

 private:
        // std::map<std::string, struct client> clients_;
};

#endif   // CHATSERVER_H
