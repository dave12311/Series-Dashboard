#ifndef SERIES_DASHBOARD_SERIESDASHBOARD_H
#define SERIES_DASHBOARD_SERIESDASHBOARD_H

#include <glibmm/refptr.h>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/stack.h>

class SeriesDashboard {
public:
	int status = -1;

	SeriesDashboard(int argc, char *argv[]);

private:
	Glib::RefPtr<Gtk::Application> app;
	Glib::RefPtr<Gtk::Builder> builder;

	Gtk::Window *window;
	Gtk::Stack *stack;
};


#endif
