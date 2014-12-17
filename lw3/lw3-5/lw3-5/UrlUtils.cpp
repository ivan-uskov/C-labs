#include "stdafx.h"
#include "UrlUtils.h"
#include <exception>
#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>

using namespace std;

Protocol GetProtocolByText(string const& protocolText)
{
    if (protocolText == "http")
    {
        return Protocol::HTTP;
    }
    else if (protocolText == "https")
    {
        return Protocol::HTTPS;
    }
    else if (protocolText == "ftp")
    {
        return Protocol::FTP;
    }
    else
    {
        return Protocol::ERROR;
    }
}

int GetDefaultPort(Protocol const& protocol)
{
    switch (protocol)
    {
        case Protocol::HTTP:
            return DEFAULT_HTTP_PORT;
        case Protocol::HTTPS:
            return DEFAULT_HTTPS_PORT;
        case Protocol::FTP:
            return DEFAULT_FTP_PORT;
        default:
            return 0;
    }
}

int GetPortByText(string const& portText, Protocol const& protocol)
{
    try
    {
        return boost::lexical_cast<int>(portText);
    }
    catch (bad_cast const& e)
    {
        return GetDefaultPort(protocol);
    }
}

bool ParseURL(std::string const& url, Protocol & protocol, int & port, std::string & host,
    std::string & document)
{
    smatch matches;
    string urlStr(url);
    boost::algorithm::to_lower(urlStr);
    regex checker("^(http[s]?|ftp)://([^/:]+)(:([0-9]+))?(/(.*)?)?$");

    if (regex_match(urlStr, matches, checker))
    {
        protocol = GetProtocolByText(matches[1].str());
        host = matches[2].str();
        port = GetPortByText(matches[4].str(), protocol);
        document = matches[6].str();

        return true;
    }
    return false;
}