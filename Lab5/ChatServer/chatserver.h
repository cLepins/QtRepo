#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include"serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject* parent = nullptr);
protected:
    void incomingConnection(qintptr soketDescriptor) override;
    QVector<serverWorker*> m_clients;

    void broadcast(const QJsonObject &message,serverWorker* exclude);
signals:
    void logMessage(const QString& msg);



public slots:
    void stopServer();

     void jsonReceived(serverWorker* sender,const QJsonObject& docObj);

};

#endif // CHATSERVER_H
