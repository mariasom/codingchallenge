#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QString>
#include <map>
#include <iostream>
#include <utility>

// struct client {
//    int userID;
//    std::string userName;
//    std::string nameColor;
//};

class ChatServer: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged);
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged);

    // Q_INVOKABLE void reg(std::string from) {
    //     std::cout << "user" << from << "sent message\n";
    //     emit getUser(from);
    // }

    // Q_INVOKABLE void sendMessage(std::string msg) {
    //     std::cout << "message" << msg << "recieved\n";
    //     emit getMessage(msg);
    // }
 signals:
    // void update();
    void userNameChanged();
    void messageChanged();

 public slots:
    // void buttonClicked();

 public:
    explicit ChatServer(QObject *parent = nullptr);
    ~ChatServer() {}
    QString userName();
    QString message();
    void setUserName(const QString &userName);
    void setMessage(const QString &message);

 private:
    QString m_user;
    QString m_msg;
};

#endif   // CHATSERVER_H
