#include "Dashboard.h"

#include <glibmm/markup.h>
#include <iostream>

#include <gtkmm/stack.h>
#include <gtkmm/box.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/textview.h>

namespace seriesdashboard {
	Dashboard::Dashboard(int argc, char *argv[]) {
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

			// TODO: Move to AddNewWindow
			// Set up file chooser
			builder->get_widget<Gtk::FileChooserDialog>("FileDialog", fileChooserDialog);
			fileChooserDialog->add_button("Select", Gtk::ResponseType::RESPONSE_OK);

			// TODO: REMOVE -START-
			Gtk::Box *movie;
			builder->get_widget<Gtk::Box>("series", movie);

			Gtk::Widget *empty;
			builder->get_widget<Gtk::Widget>("empty", empty);
			dashboardStack->set_visible_child(*empty);
			//mainStack->set_visible_child(*static_cast<Gtk::Widget*>(movie));
			// TODO: REMOVE -END-

			// Initiate config
			try {
				config = std::make_unique<Config>();
			} catch (nlohmann::json::exception &error) {
				std::cerr << error.what() << std::endl;
				errorDialog("Could not parse config file");
			} catch (std::exception &error) {
				std::cerr << error.what() << std::endl;
				errorDialog(error.what());
			}

			// Set up preferences menu
			preferences = std::make_unique<PreferencesWindow>(config, builder);

			setupConnections();

			status = app->run(*window);
		} else {
			std::string err = "Could not initialize builder";
			std::cerr << err << std::endl;
			errorDialog(err);
		}
	}

	void Dashboard::errorDialog(const std::string& message) noexcept {
		Gtk::MessageDialog errorDialog(message);
		errorDialog.set_title("Error");
		errorDialog.run();
		app->quit();
	}

	int Dashboard::getStatus() const {
		return status;
	}

	void Dashboard::setupConnections() noexcept {
		// Add new
		Gtk::Button *addNewButton;
		builder->get_widget<Gtk::Button>("new_button", addNewButton);

		addNewButton->signal_clicked().connect(sigc::mem_fun(this, &Dashboard::onNewClicked));

		// PreferencesWindow
		Gtk::MenuItem *preferencesButton;
		builder->get_widget<Gtk::MenuItem>("menu_pref", preferencesButton);

		preferencesButton->signal_activate().connect(sigc::mem_fun(preferences.get(), &PreferencesWindow::run));
	}

	void Dashboard::onNewClicked() {
		std::string path;

		if (fileChooserDialog->run() == Gtk::ResponseType::RESPONSE_OK) {
			path = fileChooserDialog->get_filename();
		}

		fileChooserDialog->close();

		addSeries(path);
	}

	void Dashboard::addSeries(const std::string &path) {
		Entry newEntry(path);
		series.push_back(newEntry);
		// TODO: Add series
	}
}
