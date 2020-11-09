#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QString>
#include <map>
#include <iostream>
#include <utility>

class ChatServer: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged);
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged);

 signals:
    void userNameChanged();
    void messageChanged();

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
