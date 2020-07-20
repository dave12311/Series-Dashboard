#include "Dashboard.h"

#include <glibmm/markup.h>
#include <iostream>

#include <gtkmm/stack.h>
#include <gtkmm/box.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/menuitem.h>

seriesdashboard::Dashboard::Dashboard(int argc, char *argv[]) {
	app = Gtk::Application::create(argc, argv, "com.dave12311.series-dashboard");
	builder = Gtk::Builder::create();

	try {
		builder->add_from_file("../ui/Dashboard.glade");
	} catch (const Glib::MarkupError &ex) {
		std::cerr << ex.what() << std::endl;
		errorDialog(ex.what());
	} catch (const Gtk::BuilderError &ex) {
		std::cerr << ex.what() << std::endl;
		errorDialog(ex.what());
	}

	if (builder) {
		builder->get_widget<Gtk::Window>("SeriesDashboard", window);

		builder->get_widget<Gtk::Stack>("stack_main", mainStack);
		builder->get_widget<Gtk::Stack>("stack_dashboard", dashboardStack);

		builder->get_widget<Gtk::FileChooserDialog>("FileDialog", fileChooserDialog);
		fileChooserDialog->add_button("Select", Gtk::ResponseType::RESPONSE_OK);

		builder->get_widget<Gtk::Dialog>("Preferences", preferences);
		preferences->add_button("Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
		preferences->add_button("Save", Gtk::ResponseType::RESPONSE_APPLY);

		// TODO: REMOVE -START-
		Gtk::Box *movie;
		builder->get_widget<Gtk::Box>("series", movie);

		Gtk::Widget *empty;
		builder->get_widget<Gtk::Widget>("empty", empty);
		dashboardStack->set_visible_child(*empty);
		//mainStack->set_visible_child(*static_cast<Gtk::Widget*>(movie));
		// TODO: REMOVE -END-

		setupConnections();

		// Initiate config
		try {
			config = std::make_unique<seriesdashboard::Config>();
		} catch (nlohmann::json::exception &error) {
			std::cerr << error.what() << std::endl;
			errorDialog("Could not parse config file");
		} catch (std::exception &error) {
			std::cerr << error.what() << std::endl;
			errorDialog(error.what());
		}

		status = app->run(*window);
	} else {
		std::string err = "Could not initialize builder";
		std::cerr << err << std::endl;
		errorDialog(err);
	}
}

void seriesdashboard::Dashboard::errorDialog(std::string message) noexcept {
	Gtk::MessageDialog errorDialog(message);
	errorDialog.set_title("Error");
	errorDialog.run();
	app->quit();
}

int seriesdashboard::Dashboard::getStatus() {
	return status;
}

void seriesdashboard::Dashboard::setupConnections() noexcept {
	// Add new
	Gtk::Button *addNewButton;
	builder->get_widget<Gtk::Button>("new_button", addNewButton);

	addNewButton->signal_clicked().connect(sigc::mem_fun(this, &Dashboard::onNewClicked));

	// Preferences
	Gtk::MenuItem *preferencesButton;
	builder->get_widget<Gtk::MenuItem>("menu_pref", preferencesButton);

	preferencesButton->signal_activate().connect(sigc::mem_fun(this, &Dashboard::onPreferencesClicked));
}

void seriesdashboard::Dashboard::onNewClicked() {
	std::string path;

	if (fileChooserDialog->run() == Gtk::ResponseType::RESPONSE_OK) {
		path = fileChooserDialog->get_filename();
	}

	fileChooserDialog->close();

	addSeries(path);
}

void seriesdashboard::Dashboard::onPreferencesClicked() {
	int result = preferences->run();
	switch (result) {
		case Gtk::ResponseType::RESPONSE_CANCEL:
			preferences->close();
			break;
		case Gtk::RESPONSE_DELETE_EVENT:
			preferences->close();
			break;
		case Gtk::ResponseType::RESPONSE_APPLY:
			// TODO: Save regex to config
			preferences->close();
			break;
	}
}

void seriesdashboard::Dashboard::addSeries(const std::string &path) {
	seriesdashboard::Entry newEntry(path);
}
