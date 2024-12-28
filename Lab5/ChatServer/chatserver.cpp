#include "chatserver.h"
#include "serverworker.h"
#include <QJsonObject>
#include <QJsonValue>

ChatServer::ChatServer(QObject* parent)
    :QTcpServer(parent)
{


}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    serverWorker *worker = new serverWorker(this);
    if(!worker->setSocketDescriptor(socketDescriptor))
    {
        worker->deleteLater();
        return;
    }
    connect(worker,&serverWorker::logMessage,this,&ChatServer::logMessage);
    connect(worker,&serverWorker::jsonReceived,this,&ChatServer::jsonReceived);
    m_clients.append(worker);
    emit logMessage("新的用户连接上了");
}

void ChatServer::broadcast(const QJsonObject &message, serverWorker *exclude)
{
    for(serverWorker* worker:m_clients){
        worker->sendJson(message);
    }
}

void ChatServer::stopServer()
{
    close();
}

void ChatServer::jsonReceived(serverWorker* sender,const QJsonObject& docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if(typeVal.isNull() || !typeVal.isString()){
        return ;
    }
    if(typeVal.toString().compare("message",Qt::CaseInsensitive) == 0){
        const QJsonValue textVal = docObj.value("text");
        if(textVal.isNull() || !textVal.isString()){
            return;
        }
        const QString text = textVal.toString().trimmed();
        if(text.isEmpty())
            return;
        QJsonObject message;
        message["type"] = "message";
        message["text"] = text;
        message["sender"] = sender->userName();

        broadcast(message,sender);
    }else if(typeVal.toString().compare("login",Qt::CaseInsensitive) == 0){
        const QJsonValue userNameVal = docObj.value("text");
        if(userNameVal.isNull() || !userNameVal.isString()){
            return;
        }
        sender->setUserName(userNameVal.toString());
        QJsonObject connectedMessage;
        connectedMessage["type"] = "newuser";
        connectedMessage["text"] = userNameVal.toString();
        broadcast(connectedMessage,sender);
    }
}
