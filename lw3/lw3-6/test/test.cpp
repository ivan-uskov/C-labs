#include "stdafx.h"
#include "../translator/Dictionary.cpp"
#include <boost/filesystem.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(DictionaryTest)

BOOST_AUTO_TEST_CASE(CheckReadTranslationsFile)
{
    CDictionary dictionary("test_translations");
    BOOST_CHECK(dictionary.Translate("home") == "дом");
}

BOOST_AUTO_TEST_CASE(CheckAddToDictionary)
{
    CDictionary dictionary("test_translations");
    BOOST_CHECK(dictionary.Translate("ololosha").empty());
    BOOST_CHECK(dictionary.AddTranslation("ololosha", "ололоша"));
    BOOST_CHECK(dictionary.Translate("ololosha") == "ололоша");
}

BOOST_AUTO_TEST_CASE(CheckFlushNewWords)
{
    auto tempBoostPath = boost::filesystem::unique_path();
    auto tempPath = tempBoostPath.string();
    ofstream outfile(tempPath);
    outfile.close();

    CDictionary startDict(tempPath);
    BOOST_CHECK(startDict.Translate("Snowman").empty());
    BOOST_CHECK(startDict.AddTranslation("Snowman", "снеговик"));
    BOOST_CHECK(startDict.Translate("Snowman") == "снеговик");
    startDict.FlushNewWords();

    CDictionary newDict(tempPath);
    BOOST_CHECK(newDict.Translate("Snowman") == "снеговик");

    boost::filesystem::remove(tempBoostPath);
}

BOOST_AUTO_TEST_SUITE_END()