#ifndef SERIES_DASHBOARD_DASHBOARD_H
#define SERIES_DASHBOARD_DASHBOARD_H

#include <glibmm/refptr.h>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/stack.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>

namespace seriesdashboard {
	class Dashboard {
	public:
		Dashboard(int argc, char *argv[]);

		int getStatus();

	private:
		int status = -1;

		Glib::RefPtr<Gtk::Application> app;
		Glib::RefPtr<Gtk::Builder> builder;

		Gtk::Window *window;
		Gtk::Stack *mainStack;
		Gtk::Stack *dashboardStack;

		Gtk::Button *addnewButton;
		Gtk::FileChooserDialog *fileChooserDialog;


		// Number of added series
		uint16_t seriesCount = 0;

		void getBuilderWidgets();
		void setupConnections();

		void onNewClicked();
	};
}

#endif
