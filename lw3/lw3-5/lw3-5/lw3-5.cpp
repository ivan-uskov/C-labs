#include "stdafx.h"
#include "UrlUtils.h"

using namespace std;

struct UrlInfo
{
    string url;
    bool isCorrect;
    Protocol protocol;
    int port;
    string document;
    string host;
};

bool ReadUrlString(UrlInfo & info)
{
    cout << "> ";
    if (cin >> info.url && info.url != "...")
    {
        info.isCorrect = ParseURL(info.url, info.protocol, info.port, info.host, info.document);
        return true;
    }
    return false;
}

void PrintUrlInfo(UrlInfo const& info)
{
    if (info.isCorrect)
    {
        cout << "HOST: " << info.host << endl;
        cout << "PORT: " << info.port << endl;
        cout << "DOC: " << info.document << endl;
    }
    else
    {
        cout << "This URL incorrect!" << endl;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    UrlInfo info;

    cout << "Enter URL or ... if you want to exit" << endl;

    while (ReadUrlString(info))
    {
        PrintUrlInfo(info);
    }

    cout << "Bye!" << endl;

    return 0;
}

