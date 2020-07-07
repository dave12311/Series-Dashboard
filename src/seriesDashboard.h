#ifndef SERIES_DASHBOARD_SERIESDASHBOARD_H
#define SERIES_DASHBOARD_SERIESDASHBOARD_H

#include <glibmm/refptr.h>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

class seriesDashboard {
public:
	int status = -1;

	seriesDashboard(int argc, char *argv[]);

private:
	Glib::RefPtr<Gtk::Application> app;
	Glib::RefPtr<Gtk::Builder> builder;

	Gtk::Window *window;
};


#endif //SERIES_DASHBOARD_SERIESDASHBOARD_H
