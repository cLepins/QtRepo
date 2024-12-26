#include "chatserver.h"
#include "serverworker.h"

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

    m_clients.append(worker);
    emit logMessage("新的用户连接上了");
}

void ChatServer::stopServer()
{
    close();
}
