#include <boost/test/unit_test.hpp>
#include "Form.cpp"

struct GtkFixture
{
    GtkFixture()  { gtk_init(nullptr, nullptr); }
    ~GtkFixture() { }
};

BOOST_GLOBAL_FIXTURE(GtkFixture);

BOOST_AUTO_TEST_SUITE(FormTests)

BOOST_AUTO_TEST_CASE(TestSetName)
{
    Form form;
    form.setName("John");
    BOOST_CHECK_EQUAL(form.getErrors()["name"], "");
}

BOOST_AUTO_TEST_CASE(TestSetWrongName)
{
    Form form;
    form.setName("John1");
    BOOST_CHECK_EQUAL(form.getErrors()["name"], "Invalid name");
}

BOOST_AUTO_TEST_CASE(TestSetFirstName)
{
    Form form;
    form.setFirstName("Doe");
    BOOST_CHECK_EQUAL(form.getErrors()["firstName"], "");
}

BOOST_AUTO_TEST_CASE(TestSetWrongFirstName)
{
    Form form;
    form.setFirstName("Doe1");
    BOOST_CHECK_EQUAL(form.getErrors()["firstName"], "Invalid firstname");
}

BOOST_AUTO_TEST_CASE(TestSetMail)
{
    Form form;
    form.setMail("john.doe@example.com");
    BOOST_CHECK_EQUAL(form.getErrors()["email"], "");
}

BOOST_AUTO_TEST_CASE(TestSetWrongMail)
{
    Form form;
    form.setMail("john.doe@example");
    BOOST_CHECK_EQUAL(form.getErrors()["email"], "Invalid email");
}

BOOST_AUTO_TEST_CASE(TestSetBirthday)
{
    Form form;
    form.setBirthday("1990-01-01");
    BOOST_CHECK_EQUAL(form.getErrors()["birthday"], "");
}

BOOST_AUTO_TEST_CASE(TestSetWrongBirthday)
{
    Form form;
    form.setBirthday("01-1991-01");
    BOOST_CHECK_EQUAL(form.getErrors()["birthday"], "Invalid date");
}

BOOST_AUTO_TEST_CASE(TestAgeInvalidArgument)
{
    Form form;
    BOOST_CHECK_THROW(form.validateAge("2045-13-13"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestSetCity)
{
    Form form;
    form.setCity("New York");
    BOOST_CHECK_EQUAL(form.getErrors()["city"], "");
}

BOOST_AUTO_TEST_CASE(TestSetZipCode)
{
    Form form;
    form.setZipCode("12345");
    BOOST_CHECK_EQUAL(form.getErrors()["zipCode"], "");
}

BOOST_AUTO_TEST_CASE(TestSetWrongZipCode)
{
    Form form;
    form.setZipCode("1234");
    BOOST_CHECK_EQUAL(form.getErrors()["zipCode"], "Invalid ZIP code");
}

BOOST_AUTO_TEST_CASE(TestIsValid)
{
    Form form;
    form.setName("John");
    form.setFirstName("Doe");
    form.setMail("john.doe@example.com");
    form.setBirthday("1990-01-01");
    form.setCity("New York");
    form.setZipCode("12345");
    BOOST_CHECK_EQUAL(form.isValid(), true);
}

BOOST_AUTO_TEST_CASE(TestIsNotValid)
{
    Form form;
    form.setName("John");
    form.setFirstName("Doe");
    form.setMail("");
    form.setBirthday("1990-01-01");
    form.setCity("New York");
    form.setZipCode("12345");
    BOOST_CHECK_EQUAL(form.isValid(), false);
}

BOOST_AUTO_TEST_CASE(TestIsEmpty)
{
    Form form;
    std::vector<std::string> entries = { "", "", "", "", "", "" };
    BOOST_CHECK_EQUAL(form.isEmpty(entries), true);
}

BOOST_AUTO_TEST_CASE(TestIsNotEmpty)
{
    Form form;
    std::vector<std::string> entries = { "John", "Doe", "john.doe@example.com", "1990-01-01", "12345", "New York" };
    BOOST_CHECK_EQUAL(form.isEmpty(entries), false);
}

BOOST_AUTO_TEST_CASE(TestPrintErrors)
{
    Form form;
    form.setName("John");
    form.setFirstName("Doe");
    form.setMail("");
    form.setBirthday("1990-01-01");
    form.setCity("New York");
    form.setZipCode("12345");
    if (!form.isValid())
        form.printErrors();
}

BOOST_AUTO_TEST_SUITE_END()