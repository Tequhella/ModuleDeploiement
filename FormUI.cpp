#include "Form.cpp"
#include <gtkmm-3.0/gtkmm.h>

/**
 * @brief Represents a user interface for a form.
 * 
 * The FormUI class provides a graphical user interface for a form that contains several fields such as name, email, date of birth, etc.
 * It allows the user to fill in the form, validate the input, and save the data to a file.
 * If the form is not valid, error messages are displayed in red.
 */
class FormUI {
private:
    Form form;

    std::unique_ptr<Gtk::Entry> entryNom;
    std::unique_ptr<Gtk::Entry> entryPrenom;
    std::unique_ptr<Gtk::Entry> entryMail;
    std::unique_ptr<Gtk::Entry> entryDate;
    std::unique_ptr<Gtk::Entry> entryCodePostal;
    std::unique_ptr<Gtk::Entry> entryVille;

    std::unique_ptr<Gtk::Label> errorNom;
    std::unique_ptr<Gtk::Label> errorPrenom;
    std::unique_ptr<Gtk::Label> errorMail;
    std::unique_ptr<Gtk::Label> errorDate;
    std::unique_ptr<Gtk::Label> errorCodePostal;
    std::unique_ptr<Gtk::Label> errorVille;

    Gtk::Button button;

public:
    FormUI() {}

    void onButtonClicked()
    {
        // Reset error labels
        errorNom->set_text("");
        errorPrenom->set_text("");
        errorMail->set_text("");
        errorDate->set_text("");
        errorCodePostal->set_text("");
        errorVille->set_text("");

        // Does not seem to be necessary, but in case the validate button is bypassed by the user, a double check is done
        if (form.isEmpty(std::vector<std::string> { entryNom->get_text(), entryPrenom->get_text(), entryMail->get_text(), entryDate->get_text(), entryCodePostal->get_text(), entryVille->get_text() }))
        {
            if (entryNom->get_text().empty())
                errorNom->set_text("Veuillez remplir le champ nom.");
            if (entryPrenom->get_text().empty())
                errorPrenom->set_text("Veuillez remplir le champ prénom.");
            if (entryMail->get_text().empty())
                errorMail->set_text("Veuillez remplir le champ mail.");
            if (entryDate->get_text().empty())
                errorDate->set_text("Veuillez remplir le champ date de naissance.");
            if (entryCodePostal->get_text().empty())
                errorCodePostal->set_text("Veuillez remplir le champ code postal.");
            if (entryVille->get_text().empty())
                errorVille->set_text("Veuillez remplir le champ ville.");
            
            return;
        }
        form.setName(entryNom->get_text());
        form.setFirstName(entryPrenom->get_text());
        form.setMail(entryMail->get_text());
        form.setBirthday(entryDate->get_text());
        form.setZipCode(entryCodePostal->get_text());
        form.setCity(entryVille->get_text());
        
        // Check if the form is valid and print errors if not
        if (!form.isValid())
        {
            if (form.getErrors()["name"] != "")
                errorNom->set_text(form.getErrors()["name"]);
            if (form.getErrors()["firstName"] != "")
                errorPrenom->set_text(form.getErrors()["firstName"]);
            if (form.getErrors()["email"] != "")
                errorMail->set_text(form.getErrors()["email"]);
            if (form.getErrors()["birthday"] != "")
                errorDate->set_text(form.getErrors()["birthday"]);
            if (form.getErrors()["zipCode"] != "")
                errorCodePostal->set_text(form.getErrors()["zipCode"]);
            if (form.getErrors()["city"] != "")
                errorVille->set_text(form.getErrors()["city"]);
            
            return;
        }

        form.saveData("data.txt");

        form.printErrors();
    }

    /**
     * @brief Create a new window with a form.
     * 
     * This function creates a new window with a form to fill in.
     * The form contains the following fields:
     * - Nom
     * - Prénom
     * - Mail
     * - Date de naissance
     * - Code postal
     * - Ville
     * 
     * The form also contains a "Valider" button that is disabled until all fields are filled in.
     * When the button is clicked, the form is validated and the data is saved to a file.
     * If the form is not valid, the errors are displayed in red.
     */
    void fenetre()
    {
        // Create a new application
        Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("org.gtkmm.example");
        
        // Create a new window with a default size of 800x800
        Gtk::Window window;
        window.set_default_size(800, 800);
        
        // Create a new vertical box and add it to the window
        Gtk::Box box(Gtk::ORIENTATION_VERTICAL);
        window.add(box);
        
        // Create a new entry for each field, using smart pointers
        entryNom        = std::make_unique<Gtk::Entry>();
        entryPrenom     = std::make_unique<Gtk::Entry>();
        entryMail       = std::make_unique<Gtk::Entry>();
        entryDate       = std::make_unique<Gtk::Entry>();
        entryCodePostal = std::make_unique<Gtk::Entry>();
        entryVille      = std::make_unique<Gtk::Entry>();

        // Create a new label with the text "Nom" and add the label to the box.
        Gtk::Label label("Nom");
        box.pack_start(label);
        // Create a new entry Nom and add the entry to the box
        box.pack_start(*entryNom);
        entryNom->signal_changed().connect(sigc::mem_fun(*this, &FormUI::onEntryChanged));

        // Create a new label with the text "Prénom" and add the label to the box.
        Gtk::Label label2("Prénom");
        box.pack_start(label2);
        // Create a new entry Prénom and add the entry to the box
        box.pack_start(*entryPrenom);
        entryPrenom->signal_changed().connect(sigc::mem_fun(*this, &FormUI::onEntryChanged));
        
        // Create a new label with the text "Mail" and add the label to the box.
        Gtk::Label label3("Mail");
        box.pack_start(label3);
        // Create a new entry Mail and add the entry to the box
        box.pack_start(*entryMail);
        entryMail->signal_changed().connect(sigc::mem_fun(*this, &FormUI::onEntryChanged));

        // Create a new label with the text "Date de naissance" and add the label to the box.
        Gtk::Label label4("Date de naissance");
        box.pack_start(label4);
        // Create a new entry Date de naissance and add the entry to the box
        box.pack_start(*entryDate);
        entryDate->signal_changed().connect(sigc::mem_fun(*this, &FormUI::onEntryChanged));

        // Create a new label with the text "Code postal" and add the label to the box.
        Gtk::Label label5("Code postal");
        box.pack_start(label5);
        // Create a new entry Code postal and add the entry to the box
        box.pack_start(*entryCodePostal);
        entryCodePostal->signal_changed().connect(sigc::mem_fun(*this, &FormUI::onEntryChanged));
        
        // Create a new label with the text "Ville" and add the label to the box.
        Gtk::Label label6("Ville");
        box.pack_start(label6);
        // Create a new entry Ville and add the entry to the box
        box.pack_start(*entryVille);
        entryVille->signal_changed().connect(sigc::mem_fun(*this, &FormUI::onEntryChanged));

        // Create error labels and add them to the box
        errorNom = std::make_unique<Gtk::Label>();
        errorNom->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        box.pack_start(*errorNom);

        errorPrenom = std::make_unique<Gtk::Label>();
        errorPrenom->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        box.pack_start(*errorPrenom);

        errorMail = std::make_unique<Gtk::Label>();
        errorMail->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        box.pack_start(*errorMail);

        errorDate = std::make_unique<Gtk::Label>();
        errorDate->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        box.pack_start(*errorDate);

        errorCodePostal = std::make_unique<Gtk::Label>();
        errorCodePostal->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        box.pack_start(*errorCodePostal);

        errorVille = std::make_unique<Gtk::Label>();
        errorVille->override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        box.pack_start(*errorVille);
        
        // Create a new button "Valider" and add the button to the box.
        // Connect the signal "clicked" to the function onButtonClicked.
        // Add the button to the box.
        button = Gtk::Button("Valider");
        button.signal_clicked().connect(sigc::mem_fun(*this, &FormUI::onButtonClicked));
        box.pack_start(button);

        // Disable the button by default
        button.set_sensitive(false);

        // Show all children of the window
        window.show_all_children();

        // Run the application
        app->run(window);
    }

    void onEntryChanged()
    {
        // Enable the button if all fields are filled in
        button.set_sensitive(!entryNom->get_text().empty() && !entryPrenom->get_text().empty() && !entryMail->get_text().empty() && !entryDate->get_text().empty() && !entryCodePostal->get_text().empty() && !entryVille->get_text().empty());
    }
};