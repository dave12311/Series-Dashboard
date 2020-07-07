#include "seriesDashboard.h"

#include <glibmm/markup.h>
#include <iostream>

seriesDashboard::seriesDashboard(int argc, char *argv[]) {
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
		builder->get_widget<Gtk::Window>("seriesDashboard", window);
		status = app->run(*window);
	} else {
		status = 404;
	}
}