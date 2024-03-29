#include "Form.cpp"
#include <gtkmm-3.0/gtkmm.h>

class FormUI {
private:
    Form form;

    std::unique_ptr<Gtk::Entry> entryNom;
    std::unique_ptr<Gtk::Entry> entryPrenom;
    std::unique_ptr<Gtk::Entry> entryMail;
    std::unique_ptr<Gtk::Entry> entryDate;
    std::unique_ptr<Gtk::Entry> entryCodePostal;
    std::unique_ptr<Gtk::Entry> entryVille;

public:
    FormUI() {}

    void onButtonClicked()
    {
        if (form.isEmpty(std::vector<std::string> { entryNom->get_text(), entryPrenom->get_text(), entryMail->get_text(), entryDate->get_text(), entryCodePostal->get_text(), entryVille->get_text() }))
        {
            if (entryNom->get_text().empty())
                form.getErrors()["name"] = "Veuillez remplir le champ nom.";
            if (entryPrenom->get_text().empty())
                form.getErrors()["firstName"] = "Veuillez remplir le champ prénom.";
            if (entryMail->get_text().empty())
                form.getErrors()["email"] = "Veuillez remplir le champ mail.";
            if (entryDate->get_text().empty())
                form.getErrors()["birthday"] = "Veuillez remplir le champ date de naissance.";
            if (entryCodePostal->get_text().empty())
                form.getErrors()["zipCode"] = "Veuillez remplir le champ code postal.";
            if (entryVille->get_text().empty())
                form.getErrors()["city"] = "Veuillez remplir le champ ville.";
            
            return;
        }
        form.setName(entryNom->get_text());
        form.setFirstName(entryPrenom->get_text());
        form.setMail(entryMail->get_text());
        form.setBirthday(entryDate->get_text());
        form.setZipCode(entryCodePostal->get_text());
        form.setCity(entryVille->get_text());

        form.printErrors();
    }

    /**
     * @brief Crée une fenêtre d'application GTK avec divers champs de saisie et un bouton.
     * 
     * Cette fonction crée une fenêtre d'application GTK en utilisant la classe Gtk::Application. Elle définit la taille par défaut de la fenêtre à 800x800 pixels.
     * Elle crée un conteneur de boîte verticale et l'ajoute à la fenêtre. À l'intérieur de la boîte, elle crée plusieurs étiquettes et champs de saisie pour capturer les informations de l'utilisateur.
     * Enfin, elle crée un bouton intitulé "Valider" et connecte son signal "clicked" à la méthode onButtonClicked de la classe FormUI.
     * La fonction affiche ensuite tous les enfants de la fenêtre et exécute l'application.
     */
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
        
        entryNom        = std::make_unique<Gtk::Entry>();
        entryPrenom     = std::make_unique<Gtk::Entry>();
        entryMail       = std::make_unique<Gtk::Entry>();
        entryDate       = std::make_unique<Gtk::Entry>();
        entryCodePostal = std::make_unique<Gtk::Entry>();
        entryVille      = std::make_unique<Gtk::Entry>();

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
        button.signal_clicked().connect(sigc::mem_fun(*this, &FormUI::onButtonClicked));
        box.pack_start(button);

        // Affiche tous les enfants de la fenêtre.
        window.show_all_children();

        // Exécute l'application.
        app->run(window);
    }
};