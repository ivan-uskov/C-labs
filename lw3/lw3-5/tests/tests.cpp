#include "stdafx.h"
#include "../lw3-5/UrlUtils.cpp"

using namespace std;

struct UrlUtilsTestsFixture
{
    Protocol protocol;
    int port;
    string host;
    string document;
};

BOOST_FIXTURE_TEST_SUITE(UrlUtilsTests, UrlUtilsTestsFixture)

BOOST_AUTO_TEST_CASE(SimpleUrl)
{
    BOOST_CHECK(ParseURL("http://google.com/", protocol, port, host, document));
    BOOST_CHECK(protocol == Protocol::HTTP);
    BOOST_CHECK(host == "google.com");
    BOOST_CHECK(port == DEFAULT_HTTP_PORT);
    BOOST_CHECK(document == "");
}

BOOST_AUTO_TEST_CASE(SimpleUrlWithOutLastSlashAndDefaultPort)
{
    BOOST_CHECK(ParseURL("https://yandex.com", protocol, port, host, document));
    BOOST_CHECK(protocol == Protocol::HTTPS);
    BOOST_CHECK(host == "yandex.com");
    BOOST_CHECK(port == DEFAULT_HTTPS_PORT);
    BOOST_CHECK(document == "");
}


BOOST_AUTO_TEST_CASE(SimpleUrlWithPort)
{
    BOOST_CHECK(ParseURL("http://google.com:443", protocol, port, host, document));
    BOOST_CHECK(protocol == Protocol::HTTP);
    BOOST_CHECK(host == "google.com");
    BOOST_CHECK(port == 443);
    BOOST_CHECK(document == "");
}

BOOST_AUTO_TEST_CASE(SimpleUrlWithPortAndDocument)
{
    BOOST_CHECK(ParseURL("ftp://google.com:80/kotiki.png", protocol, port, host, document));
    BOOST_CHECK(protocol == Protocol::FTP);
    BOOST_CHECK(host == "google.com");
    BOOST_CHECK(port == 80);
    BOOST_CHECK(document == "kotiki.png");
}

BOOST_AUTO_TEST_CASE(SimpleIncorrectUrl)
{
    BOOST_CHECK(!ParseURL("ololo://google.com:a/kotiki.png", protocol, port, host, document));
}


BOOST_AUTO_TEST_SUITE_END()