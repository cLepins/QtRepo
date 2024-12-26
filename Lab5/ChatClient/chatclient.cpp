#include "chatclient.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>


ChatClient::ChatClient(QObject *parent)
    : QObject{parent}
{}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_12);
    for(;;)
    {
        socketStream.startTransaction();
        socketStream>>jsonData;
        if(socketStream.commitTransaction()){
            emit messageRecieved(QString::fromUtf8(jsonData));
            sendMessage("I recieved message");
        }else {
            break;
        }
    }
}

void ChatClient::sendMessage(const QString &text, const QString &type)
{
    if(this->m_clientSocket->state() != QAbstractSocket::ConnectedState)
        return;
    if(!text.isEmpty()){
        QDataStream serverStream(m_clientSocket);
        serverStream.setVersion(QDataStream::Qt_5_12);

        QJsonObject message;

        message["type"] = type;
        message["text"] = text;
        serverStream << QJsonDocument(message).toJson();
    }
}

void ChatClient::connetToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address,port);
}
