Qt-SslServer
============

Tcp Server class with SSL support using QTcpServer and QSslSocket. Requires Qt and -std=c++11 to compile. An OpenSSL implementation must also be available on the target machine.


Example
============

See "example" directory.

*.pem and *.key files MUST be in the working directory of Client and Server (Client only needs sslserver.pem while Server needs both sslserver.pem and sslserver.key).

If you're running Windows, you probably have no OpenSSL installation on your system. You may need to install Win32 OpenSSL "Light" version (here: http://slproweb.com/products/Win32OpenSSL.html).
