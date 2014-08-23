/**
 * Qt-SslServer, a Tcp Server class with SSL support using QTcpServer and QSslSocket.
 * Copyright (C) 2014  TRUCHOT Guillaume
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "ServerExample.h"

#include "SslServer.h"

#include <QCoreApplication>
#include <QHostAddress>
#include <QSslSocket>
#include <QThread>

ServerExample::ServerExample(QObject *parent) : QObject(parent)
{
}


void ServerExample::run()
{
    QHostAddress address = QHostAddress::Any;
    quint16 port = 22333;

    SslServer sslServer;
    sslServer.setSslLocalCertificate("sslserver.pem");
    sslServer.setSslPrivateKey("sslserver.key");
    sslServer.setSslProtocol(QSsl::TlsV1_2);

    if (sslServer.listen(address, port))
        qDebug().nospace() << "Now listening on " << qPrintable(address.toString()) << ":" << port;
    else
        qDebug().nospace() << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port;

    if (sslServer.waitForNewConnection(-1))    // Wait until a new connection is received, -1 means no timeout
    {
        qDebug() << "New connection";
        QSslSocket *sslSocket = dynamic_cast<QSslSocket*>(sslServer.nextPendingConnection());

        if (sslSocket->waitForReadyRead(5000))    // Wait until some data is received, 5000 ms timeout (-1 doesn't work here)
        {
            QByteArray message = sslSocket->readAll();    // Read message
            qDebug() << "Message:" << QString(message);

            sslSocket->disconnectFromHost();    // Disconnect
            sslSocket->waitForDisconnected();    // Wait until disconnected
            qDebug() << "Disconnected";
        }

        else
        {
            qDebug().nospace() << "ERROR: could not receive message (" << qPrintable(sslSocket->errorString()) << ")";
        }
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslServer.errorString()) << ")";
    }

    this->deleteLater();
    QThread::currentThread()->quit();
    qApp->exit();
}
