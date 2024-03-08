#include <regex>
#include <map>
#include <gtkmm-3.0/gtkmm.h>
#include "Age.cpp"

class Form {
private:
    std::string name;
    std::string firstName;
    std::string mail;
    std::string birthday;
    std::string city;
    std::string zipCode;

    std::map<std::string, std::string> errors;

public:
    Form()
    {
        errors["email"] = "";
        errors["name"] = "";
        errors["firstName"] = "";
        errors["birthday"] = "";
        errors["zipCode"] = "";
    }

    void setName(const std::string& name)
    {
        this->name = name;
        validateName(name);
    }

    void setFirstName(const std::string& firstName)
    {
        this->firstName = firstName;
        validateFirstname(firstName);
    }

    void setMail(const std::string& mail)
    {
        this->mail = mail;
        validateEmail(mail);
    }

    void setBirthday(const std::string& birthday)
    {
        this->birthday = birthday;
        validateAge(birthday);
    }

    void setCity(const std::string& city)
    {
        this->city = city;
    }

    void setZipCode(const std::string& zipCode)
    {
        this->zipCode = zipCode;
        validateZIP(zipCode);
    }

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

    std::map<std::string, std::string> getErrors()
    {
        return errors;
    }

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

    std::string getError(const std::string& key)
    {
        return errors[key];
    }

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
};