#include "stdafx.h"

const int DEFAULT_HTTP_PORT= 80;
const int DEFAULT_HTTPS_PORT = 443;
const int DEFAULT_FTP_PORT = 21;


enum class Protocol
{
    HTTP,
    HTTPS,
    FTP,
    ERROR
};

bool ParseURL(std::string const& url, Protocol & protocol, int & port, std::string & host,
    std::string & document);