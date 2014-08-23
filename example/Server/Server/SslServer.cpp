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


#include "SslServer.h"

#include <QFile>
#include <QSslSocket>

SslServer::SslServer(QObject *parent) : QTcpServer(parent),
    m_sslLocalCertificate(),
    m_sslPrivateKey(),
    m_sslProtocol(QSsl::UnknownProtocol)
{
}


void SslServer::incomingConnection(qintptr socketDescriptor)
{
    // Create socket
    QSslSocket *sslSocket = new QSslSocket(this);
    sslSocket->setSocketDescriptor(socketDescriptor);
    sslSocket->setLocalCertificate(m_sslLocalCertificate);
    sslSocket->setPrivateKey(m_sslPrivateKey);
    sslSocket->setProtocol(m_sslProtocol);
    sslSocket->startServerEncryption();

    // Add to the internal list of pending connections (see Qt doc: http://qt-project.org/doc/qt-5/qtcpserver.html#addPendingConnection)
    this->addPendingConnection(sslSocket);
}




const QSslCertificate &SslServer::getSslLocalCertificate() const
{
    return m_sslLocalCertificate;
}

const QSslKey &SslServer::getSslPrivateKey() const
{
    return m_sslPrivateKey;
}

QSsl::SslProtocol SslServer::getSslProtocol() const
{
    return m_sslProtocol;
}



void SslServer::setSslLocalCertificate(const QSslCertificate &certificate)
{
    m_sslLocalCertificate = certificate;
}

bool SslServer::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        return false;

    m_sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}


void SslServer::setSslPrivateKey(const QSslKey &key)
{
    m_sslPrivateKey = key;
}

bool SslServer::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile(fileName);

    if (!keyFile.open(QIODevice::ReadOnly))
        return false;

    m_sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}


void SslServer::setSslProtocol(QSsl::SslProtocol protocol)
{
    m_sslProtocol = protocol;
}
