#include "chatserver.h"

ChatServer::ChatServer(QObject *parent) : QObject(parent) {
}

QString ChatServer::userName() {
    return m_user;
}

QString ChatServer::message() {
    return m_msg;
}

void ChatServer::setUserName(const QString &userName) {
    if (userName.compare(m_user) == 0)
        return;

    m_user = userName;
    emit userNameChanged();
}

void ChatServer::setMessage(const QString &msg) {
    if (msg.compare(m_msg) == 0)
        return;

    m_msg = msg;
    emit messageChanged();
}