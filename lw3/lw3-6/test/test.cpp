#include "stdafx.h"
#include "../translator/Dictionary.cpp"
#include <boost/filesystem.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(DictionaryTest)

BOOST_AUTO_TEST_CASE(CheckReadTranslationsFile)
{
    CDictionary dictionary("test_translations");
    BOOST_CHECK(dictionary("home") == "���");
}

BOOST_AUTO_TEST_CASE(CheckAddToDictionary)
{
    CDictionary dictionary("test_translations");
    BOOST_CHECK(dictionary("ololosha").empty());
    BOOST_CHECK(dictionary.Add("ololosha", "�������"));
    BOOST_CHECK(dictionary("ololosha") == "�������");
}

BOOST_AUTO_TEST_CASE(CheckFlushNewWords)
{
    auto tempBoostPath = boost::filesystem::unique_path();
    auto tempPath = tempBoostPath.string();
    ofstream outfile(tempPath);
    outfile.close();

    CDictionary startDict(tempPath);
    BOOST_CHECK(startDict("Snowman").empty());
    BOOST_CHECK(startDict.Add("Snowman", "��������"));
    BOOST_CHECK(startDict("Snowman") == "��������");
    startDict.FlushNewWords();

    CDictionary newDict(tempPath);
    BOOST_CHECK(newDict("Snowman") == "��������");

    boost::filesystem::remove(tempBoostPath);
}

BOOST_AUTO_TEST_SUITE_END()