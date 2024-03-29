#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTests
#include <boost/test/unit_test.hpp>
#include "Age.cpp"

BOOST_AUTO_TEST_SUITE(AgeTests)

BOOST_AUTO_TEST_CASE(TestCalculateAge)
{
    /**************EQUAL**************/
    // Test 1
    Date birth1 = { 1990, 1, 1 };
    BOOST_CHECK_EQUAL(Date::calculateAge(&birth1), 34);

    // Test 2
    Date birth2 = { 2000, 1, 1 };
    BOOST_CHECK_EQUAL(Date::calculateAge(&birth2), 24);

    /*************NOT EQUAL************/
    // Test 4
    Date birth4 = { 1990, 1, 1 };
    BOOST_CHECK_NE(Date::calculateAge(&birth4), 35);

    // Test 5
    Date birth5 = { 2000, 1, 1 };
    BOOST_CHECK_NE(Date::calculateAge(&birth5), 25);

    /*************LESS************/
    // Test 7
    Date birth7 = { 1990, 1, 1 };
    BOOST_CHECK_LT(Date::calculateAge(&birth7), 35);

    // Test 8
    Date birth8 = { 2000, 8, 8 };
    BOOST_CHECK_LT(Date::calculateAge(&birth8), 25);
}

BOOST_AUTO_TEST_SUITE_END()

// Additional tests

BOOST_AUTO_TEST_SUITE(AdditionalAgeTests)

BOOST_AUTO_TEST_CASE(TestCalculateAgeInvalidObject)
{
    // Test 1
    //int invalidObject = 10;
    //BOOST_CHECK_THROW(Date::calculateAge(reinterpret_cast<Date*>(&invalidObject)), std::invalid_argument);

    // should return an invalid argument exception with the message "Mauvais objet envoyé"
    class TestClass {};

    TestClass* invalidObject = new TestClass();

    BOOST_CHECK_EXCEPTION(
        Date::calculateAge(reinterpret_cast<Date*>(invalidObject)),
        std::invalid_argument,
        [](const std::invalid_argument& e)
        {
            BOOST_TEST_MESSAGE("Exception thrown: " << e.what());
            return std::string(e.what()) == "Mauvais objet envoyé";
        }
    );

    delete invalidObject;
}

BOOST_AUTO_TEST_CASE(TestCalculateAgeNoArgument)
{
    // Test 1
    BOOST_CHECK_EXCEPTION(
        Date::calculateAge(nullptr),
        std::invalid_argument,
        [](const std::invalid_argument& e)
        {
            BOOST_TEST_MESSAGE("Exception thrown: " << e.what());
            return std::string(e.what()) == "Aucun argument envoyé";
        }
    );
}

BOOST_AUTO_TEST_CASE(TestCalculateAgeFutureDate)
{
    // Test 1
    Date birth = { 2030, 1, 1 };
    BOOST_CHECK_EXCEPTION(
        Date::calculateAge(&birth),
        std::invalid_argument,
        [](const std::invalid_argument& e)
        {
            BOOST_TEST_MESSAGE("Exception thrown: " << e.what());
            return std::string(e.what()) == "La date envoyée est fausse";
        }
    );
}

BOOST_AUTO_TEST_CASE(TestCalculateAgeMinor)
{
    // Test 1
    Date birth = { 2010, 1, 1 };
    BOOST_CHECK_EXCEPTION(
        Date::calculateAge(&birth),
        std::invalid_argument,
        [](const std::invalid_argument& e)
        {
            BOOST_TEST_MESSAGE("Exception thrown: " << e.what());
            return std::string(e.what()) == "La personne est mineure";
        }
    );
}

BOOST_AUTO_TEST_SUITE_END()