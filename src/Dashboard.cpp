#include "Dashboard.h"

#include <glibmm/markup.h>
#include <iostream>

#include <gtkmm/stack.h>
#include <gtkmm/box.h>

seriesdashboard::Dashboard::Dashboard(int argc, char *argv[]) {
	app = Gtk::Application::create(argc, argv, "com.dave12311.series-dashboard");
	builder = Gtk::Builder::create();

	try {
		builder->add_from_file("../ui/Dashboard.glade");
	} catch (const Glib::MarkupError &ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	} catch (const Gtk::BuilderError &ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}

	if (builder) {
		getBuilderWidgets();

		Gtk::Box *movie;
		builder->get_widget<Gtk::Box>("series", movie);

		Gtk::Widget *empty;
		builder->get_widget<Gtk::Widget>("empty", empty);
		dashboardStack->set_visible_child(*empty);
		//mainStack->set_visible_child(*static_cast<Gtk::Widget*>(movie));

		setupConnections();

		status = app->run(*window);
	} else {
		std::cerr << "Could not initialize builder" << std::endl;
		status = 100;
	}
}

int seriesdashboard::Dashboard::getStatus() {
	return status;
}

void seriesdashboard::Dashboard::getBuilderWidgets() {
	builder->get_widget<Gtk::Window>("SeriesDashboard", window);
	builder->get_widget<Gtk::Stack>("stack_main", mainStack);
	builder->get_widget<Gtk::Stack>("stack_dashboard", dashboardStack);
	builder->get_widget<Gtk::Button>("new_button", addnewButton);
	builder->get_widget<Gtk::FileChooserDialog>("FileDialog", fileChooserDialog);
}

void seriesdashboard::Dashboard::setupConnections() {
	addnewButton->signal_clicked().connect(sigc::mem_fun(this, &Dashboard::onNewClicked));
}

void seriesdashboard::Dashboard::onNewClicked() {
	fileChooserDialog->add_button("Select", Gtk::ResponseType::RESPONSE_OK);

	std::string path;

	if (fileChooserDialog->run() == Gtk::ResponseType::RESPONSE_OK) {
		path = fileChooserDialog->get_filename();
	}

	fileChooserDialog->close();

	std::cout << path << std::endl;
}
