#ifndef SERIES_DASHBOARD_PREFERENCESWINDOW_H
#define SERIES_DASHBOARD_PREFERENCESWINDOW_H

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/textbuffer.h>
#include <glibmm/refptr.h>

#include "Config.h"

namespace seriesdashboard {
	class PreferencesWindow {
	public:
		PreferencesWindow(std::unique_ptr<Config> &c, Glib::RefPtr<Gtk::Builder> b);

		void run();

	private:
		Glib::RefPtr<Gtk::Builder> builder;
		Gtk::Dialog *dialog;

		std::unique_ptr<Config> &config;

		Glib::RefPtr<Gtk::TextBuffer> nameRegExBuffer, episodeRegExBuffer;
	};
}


#endif //SERIES_DASHBOARD_PREFERENCESWINDOW_H
