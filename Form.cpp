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

    std::unique_ptr<Gtk::Entry> entryNom;
    std::unique_ptr<Gtk::Entry> entryPrenom;
    std::unique_ptr<Gtk::Entry> entryMail;
    std::unique_ptr<Gtk::Entry> entryDate;
    std::unique_ptr<Gtk::Entry> entryCodePostal;
    std::unique_ptr<Gtk::Entry> entryVille;

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

    bool isEmpty()
    {
        return entryNom->get_text().empty()        ||
               entryPrenom->get_text().empty()     ||
               entryMail->get_text().empty()       ||
               entryDate->get_text().empty()       ||
               entryCodePostal->get_text().empty() || 
               entryVille->get_text().empty();
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

    void onButtonClicked()
    {
        if (isEmpty())
        {
            if (entryNom->get_text().empty())
                errors["name"] = "Veuillez remplir le champ nom.";
            if (entryPrenom->get_text().empty())
                errors["firstName"] = "Veuillez remplir le champ prénom.";
            if (entryMail->get_text().empty())
                errors["email"] = "Veuillez remplir le champ mail.";
            if (entryDate->get_text().empty())
                errors["birthday"] = "Veuillez remplir le champ date de naissance.";
            if (entryCodePostal->get_text().empty())
                errors["zipCode"] = "Veuillez remplir le champ code postal.";
            if (entryVille->get_text().empty())
                errors["city"] = "Veuillez remplir le champ ville.";
            
            return;
        }
        setName(entryNom->get_text());
        setFirstName(entryPrenom->get_text());
        setMail(entryMail->get_text());
        setBirthday(entryDate->get_text());
        setZipCode(entryCodePostal->get_text());
        setCity(entryVille->get_text());

        printErrors();
    }

    void fenetre()
    {
        // Crée une application GTK.
        Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("org.gtkmm.example");

        // Crée une nouvelle fenêtre et définit la taille par défaut de la fenêtre.
        Gtk::Window window;
        window.set_default_size(800, 800);

        // Crée une nouvelle boîte vertical et ajoute la boîte à la fenêtre.
        Gtk::Box box(Gtk::ORIENTATION_VERTICAL);
        window.add(box);

        // Crée un nouveau label avec le texte "Nom" et ajoute le label à la boîte.
        Gtk::Label label("Nom");
        box.pack_start(label);
        // Crée une nouvelle entrée Nom et ajoute l'entrée à la boîte
        box.pack_start(*entryNom);

        // Crée un nouveau label avec le texte "Prénom" et ajoute le label à la boîte.
        Gtk::Label label2("Prénom");
        box.pack_start(label2);
        // Crée une nouvelle entrée Prénom et ajoute l'entrée à la boîte
        box.pack_start(*entryPrenom);

        // Crée un nouveau label avec le texte "Mail" et ajoute le label à la boîte.
        Gtk::Label label3("Mail");
        box.pack_start(label3);
        // Crée une nouvelle entrée Mail et ajoute l'entrée à la boîte
        box.pack_start(*entryMail);

        // Crée un nouveau label avec le texte "Date de naissance" et ajoute le label à la boîte.
        Gtk::Label label4("Date de naissance");
        box.pack_start(label4);
        // Crée une nouvelle entrée Date de naissance et ajoute l'entrée à la boîte
        box.pack_start(*entryDate);

        // Crée un nouveau label avec le texte "Code postal" et ajoute le label à la boîte.
        Gtk::Label label5("Code postal");
        box.pack_start(label5);
        // Crée une nouvelle entrée Code postal et ajoute l'entrée à la boîte
        box.pack_start(*entryCodePostal);

        // Crée un nouveau label avec le texte "Ville" et ajoute le label à la boîte.
        Gtk::Label label6("Ville");
        box.pack_start(label6);
        // Crée une nouvelle entrée Ville et ajoute l'entrée à la boîte
        box.pack_start(*entryVille);
        
        // Crée un nouveau bouton avec le texte "Valider".
        // Connecte le signal "clicked" du bouton à la méthode "onButtonClicked".
        // Ajoute le bouton à la boîte.
        Gtk::Button button("Valider");
        button.signal_clicked().connect(sigc::mem_fun(*this, &Form::onButtonClicked));
        box.pack_start(button);

        // Affiche tous les enfants de la fenêtre.
        window.show_all_children();

        // Exécute l'application.
        app->run(window);
    }



    
};