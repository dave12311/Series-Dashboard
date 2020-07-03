#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/stack.h>
#include <gtkmm/box.h>

#include <giomm.h>
#include <iostream>

int main(int argc, char *argv[]) {
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

	auto builder = Gtk::Builder::create();
	Gtk::Window *window;

	try {
		builder->add_from_file("../ui/Dashboard.glade");
	} catch (const Glib::FileError &ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
	} catch (const Glib::MarkupError &ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	} catch (const Gtk::BuilderError &ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}

	if (builder) {
		builder->get_widget<Gtk::Window>("SeriesDashboard", window);
	}

	return app->run(*window);
}
