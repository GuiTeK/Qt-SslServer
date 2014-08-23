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


#include "ClientExample.h"

#include <QCoreApplication>
#include <QString>
#include <QSslSocket>
#include <QThread>

ClientExample::ClientExample(QObject *parent) : QObject(parent)
{
}


void ClientExample::run()
{
    QString hostName = "127.0.0.1";    // DO NOT CHANGE THIS AS IT MUST MATCH THE FQDN OF THE CERTIFICATE (you MUST create your own certificate in order to change this)
    quint16 port = 22333;

    QSslSocket sslSocket;
    sslSocket.addCaCertificates("sslserver.pem");
    sslSocket.connectToHostEncrypted(hostName, port);

    if (sslSocket.waitForEncrypted(-1))    // Wait until encrypted connection is established, -1 means no timeout
    {
        qDebug() << "Connected";
        sslSocket.write("Hello, World!");    // Send message to the server

        if (sslSocket.waitForBytesWritten(-1))    // Wait until message is sent (also makes QSslSocket flush the buffer)
            qDebug() << "Message sent";
        else
            qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";

        while (!sslSocket.waitForDisconnected())    // Wait until disconnected
            QThread::msleep(10);

        qDebug() << "Disconnected";
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
    }

    this->deleteLater();
    QThread::currentThread()->quit();
    qApp->exit();
}
