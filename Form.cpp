#include <regex>
#include <map>
#include <gtkmm-3.0/gtkmm.h>
#include <fstream>
#include "Age.cpp"

/**
 * @brief Represents a form object.
 * 
 * The Form class is used to store and validate user input for a form. It provides methods to set and validate various form fields such as name, email, birthday, etc. It also provides methods to check if the form is valid, retrieve error messages, print errors, and save the form data to a file.
 */
class Form {
private:
    std::string name; /**< The name of the form. */
    std::string firstName; /**< The first name of the form. */
    std::string mail; /**< The email address of the form. */
    std::string birthday; /**< The birthday of the form. */
    std::string city; /**< The city of the form. */
    std::string zipCode; /**< The zip code of the form. */

    /**
     * @brief A map container that stores key-value pairs, where both the key and value are of type std::string.
     * 
     * The errors map is used to store error messages for each form field. The keys represent the field names and the values represent the error messages.
     */
    std::map<std::string, std::string> errors;

public:
    /**
     * @brief Constructs a new Form object.
     * 
     * This constructor initializes the `errors` map with empty strings for the following keys:
     * - "email"
     * - "name"
     * - "firstName"
     * - "birthday"
     * - "zipCode"
     * - "save"
     */
    Form()
    {
        errors["email"] = "";
        errors["name"] = "";
        errors["firstName"] = "";
        errors["birthday"] = "";
        errors["zipCode"] = "";
        errors["save"] = "";
    }

    /**
     * @brief Sets the name of the form.
     * 
     * This function sets the name of the form to the provided value. It also calls the validateName function to validate the name.
     * 
     * @param name The name to set.
     */
    void setName(const std::string& name)
    {
        this->name = name;
        validateName(name);
    }

    /**
     * @brief Sets the first name of the form.
     * 
     * This function sets the first name of the form to the provided value. It also calls the validateFirstname function to validate the first name.
     * 
     * @param firstName The first name to set.
     */
    void setFirstName(const std::string& firstName)
    {
        this->firstName = firstName;
        validateFirstname(firstName);
    }

    /**
     * @brief Sets the email address for the form.
     * 
     * This function sets the email address for the form and validates it using the validateEmail function.
     * 
     * @param mail The email address to be set.
     */
    void setMail(const std::string& mail)
    {
        this->mail = mail;
        validateEmail(mail);
    }

    /**
     * @brief Sets the birthday of the form.
     * 
     * This function sets the birthday of the form to the specified value. It also validates the age based on the birthday.
     * 
     * @param birthday The birthday to set.
     */
    void setBirthday(const std::string& birthday)
    {
        this->birthday = birthday;
        validateAge(birthday);
    }

    /**
     * @brief Sets the city for the form.
     * 
     * This function sets the city for the form using the provided city string.
     * 
     * @param city The city to set for the form.
     */
    void setCity(const std::string& city)
    {
        this->city = city;
    }

    /**
     * @brief Sets the zip code for the form.
     * 
     * This function sets the zip code for the form and validates it using the validateZIP function.
     * 
     * @param zipCode The zip code to set.
     */
    void setZipCode(const std::string& zipCode)
    {
        this->zipCode = zipCode;
        validateZIP(zipCode);
    }

    /**
     * @brief Validates the given name.
     * 
     * This function checks if the provided name contains only alphabetic characters.
     * If the name is invalid, it sets the corresponding error message in the `errors` map.
     * 
     * @param name The name to be validated.
     */
    void validateName(const std::string& name)
    {
        if (!std::regex_match(name, std::regex("^[a-zA-Z]+$")))
        {
            errors["name"] = "Invalid name";
        } else
        {
            errors["name"] = "";
        }
    }

    /**
     * @brief Validates the given first name.
     * 
     * This function checks if the provided first name contains only alphabetic characters.
     * If the first name is invalid, it sets the corresponding error message in the `errors` map.
     * 
     * @param firstName The first name to be validated.
     */
    void validateFirstname(const std::string& firstName)
    {
        if (!std::regex_match(firstName, std::regex("^[a-zA-Z]+$")))
        {
            errors["firstName"] = "Invalid firstname";
        } else
        {
            errors["firstName"] = "";
        }
    }

    /**
     * @brief Validates the given email address.
     * 
     * This function checks if the provided email address is in a valid format.
     * If the email address is invalid, it sets the corresponding error message in the `errors` map.
     * 
     * @param email The email address to validate.
     */
    void validateEmail(const std::string& email)
    {
        if (!std::regex_match(email, std::regex("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$")))
        {
            errors["email"] = "Invalid email";
        } else
        {
            errors["email"] = "";
        }
    }

    /**
     * @brief Validates the age based on the given birthday.
     * 
     * This function checks if the provided birthday is in a valid format and calculates the age based on the birthday.
     * If the birthday is invalid or the age is not within the valid range, it sets the corresponding error message in the `errors` map.
     * 
     * @param birthday The birthday to validate in the format "YYYY-MM-DD".
     */
    void validateAge(const std::string& birthday)
    {
        std::regex dateRegex("^(\\d{4})-(\\d{2})-(\\d{2})$");
        std::smatch match;
        if (!std::regex_match(birthday, match, dateRegex))
        {
            errors["birthday"] = "Invalid date";
        } else
        {
            int year = std::stoi(match[1]);
            int month = std::stoi(match[2]);
            int day = std::stoi(match[3]);
            Date birth = { year, month, day };
            try 
            {
                Date::calculateAge(&birth);
                errors["birthday"] = "";
            } catch (std::invalid_argument& e)
            {
                errors["birthday"] = e.what();
                throw e;
            }
        }
    }

    /**
     * @brief Validates a ZIP code.
     * 
     * This function checks if the provided ZIP code is in a valid format.
     * If the ZIP code is invalid, it sets the corresponding error message in the `errors` map.
     * 
     * @param zipCode The ZIP code to validate.
     */
    void validateZIP(const std::string& zipCode)
    {
        if (!std::regex_match(zipCode, std::regex("^\\d{5}$")))
        {
            errors["zipCode"] = "Invalid ZIP code";
        } else
        {
            errors["zipCode"] = "";
        }
    }

    /**
     * @brief Retrieves the error message associated with the given key.
     * 
     * This function returns the error message corresponding to the given key from the `errors` map.
     * 
     * @param key The key of the error message to retrieve.
     * @return The error message corresponding to the given key.
     */
    std::string getError(const std::string& key)
    {
        return errors[key];
    }

    /**
     * @brief Retrieves the errors map.
     * 
     * This function returns the `errors` map, which contains the error messages for each form field.
     * 
     * @return The errors map.
     */
    std::map<std::string, std::string> getErrors()
    {
        return errors;
    }

    /**
     * @brief Checks if the form is valid.
     * 
     * This function checks if all the form fields are valid, i.e., if all the error messages in the `errors` map are empty.
     * 
     * @return true if the form is valid, false otherwise.
     */
    bool isValid()
    {
        for (auto& error : errors)
        {
            if (!error.second.empty())
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Checks if a vector of strings is empty.
     * 
     * This function checks if any string in the provided vector is empty.
     * 
     * @param entries The vector of strings to check.
     * @return True if any string in the vector is empty, false otherwise.
     */
    bool isEmpty(std::vector<std::string> entries)
    {
        for (auto& entry : entries)
        {
            if (entry.empty())
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Prints the errors stored in the 'errors' container.
     * 
     * This function prints the error messages stored in the `errors` map to the standard output.
     */
    void printErrors()
    {
        for (auto& error : errors)
        {
            if (!error.second.empty())
            {
                std::cout << error.second << std::endl;
            }
        }
    }

    /**
     * @brief Saves the data to a file.
     * 
     * This function saves the form data to a file with the provided filename.
     * If the form is valid, it writes the form data to the file.
     * If the form is not valid, it sets an error message in the `errors` map and throws a std::runtime_error.
     * 
     * @param filename The name of the file to save the data to.
     * @throws std::runtime_error If the file could not be opened.
     */
    void saveData(const std::string& filename)
    {
        if (isValid())
        {
            // Save the data to a file
            std::ofstream file(filename);
            if (file.is_open())
            {
                file << "Nom: " << name << "\n";
                file << "Prénom: " << firstName << "\n";
                file << "Mail: " << mail << "\n";
                file << "Date de naissance: " << birthday << "\n";
                file << "Code Postal: " << zipCode << "\n";
                file << "Ville: " << city << "\n";
                file.close();

                std::cout << "Data saved successfully." << std::endl;
            }
            else
            {
                // Display an error message if the file could not be opened
                errors["save"] = "Unable to open file.";
                throw std::runtime_error("Unable to open file.");
            }
        } else
        {
            // Display an error message if the data is not valid
            std::cout << "Data not saved" << std::endl;
            errors["save"] = "Data not saved";
        }
    }
};