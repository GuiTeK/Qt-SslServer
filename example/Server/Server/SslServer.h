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


#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>
#include <QString>
#include <QSsl>
#include <QSslCertificate>
#include <QSslKey>

class SslServer : public QTcpServer
{
    Q_OBJECT

public:
    SslServer(QObject *parent = 0);



    const QSslCertificate &getSslLocalCertificate() const;
    const QSslKey &getSslPrivateKey() const;
    QSsl::SslProtocol getSslProtocol() const;


    void setSslLocalCertificate(const QSslCertificate &certificate);
    bool setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);

    void setSslPrivateKey(const QSslKey &key);
    bool setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa, QSsl::EncodingFormat format = QSsl::Pem, const QByteArray &passPhrase = QByteArray());

    void setSslProtocol(QSsl::SslProtocol protocol);


protected:
    void incomingConnection(qintptr socketDescriptor) override final;


private:
    QSslCertificate m_sslLocalCertificate;
    QSslKey m_sslPrivateKey;
    QSsl::SslProtocol m_sslProtocol;
};

#endif // SSLSERVER_H
