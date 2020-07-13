#include "SeriesDashboard.h"

#include <glibmm/markup.h>
#include <iostream>

#include <gtkmm/stack.h>
#include <gtkmm/box.h>

SeriesDashboard::SeriesDashboard(int argc, char *argv[]) {
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
		builder->get_widget<Gtk::Window>("SeriesDashboard", window);

		builder->get_widget<Gtk::Stack>("stack", stack);
		Gtk::Box *movie;
		builder->get_widget<Gtk::Box>("series", movie);
		//stack->set_visible_child(*static_cast<Gtk::Widget*>(movie));

		status = app->run(*window);
	} else {
		status = 100;
	}
}