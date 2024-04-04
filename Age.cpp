#include <iostream>
#include <ctime>

/**
 * @brief Structure representing a date.
 */
struct Date 
{
    int year; /**< The year of the date. */
    int month; /**< The month of the date. */
    int day; /**< The day of the date. */

    bool isObjectValid;

    Date(int year, int month, int day) : year(year), month(month), day(day), isObjectValid(true) {}

    /**
     * @brief Calculate the age of a person.
     * 
     * @param birth The date of birth of the person.
     * @return int The age of the person.
     */
    static int calculateAge(Date* birth)
    {
        if (!birth) 
        {
            throw std::invalid_argument("Aucun argument envoyé");
        }

        if (!birth->isObjectValid)
        {
            throw std::invalid_argument("Mauvais objet envoyé");
        }

        // Obtaining the current date
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        Date current = { now->tm_year + 1900, now->tm_mon + 1, now->tm_mday };

        // Check if the date is valid
        if (birth->year > current.year ||
            (birth->year == current.year && birth->month > current.month) ||
            (birth->year == current.year && birth->month == current.month && birth->day > current.day))
        {
            throw std::invalid_argument("La date envoyée est fausse");
        }

        // Calculate the age
        int age = current.year - birth->year;
        if (current.month < birth->month || (current.month == birth->month && current.day < birth->day)) 
        {
            age--;
        }

        if (age < 18)
        {
            throw std::invalid_argument("La personne est mineure");
        }

        return age;
    }
};