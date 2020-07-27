#ifndef SERIES_DASHBOARD_FILEBROWSERDIALOG_H
#define SERIES_DASHBOARD_FILEBROWSERDIALOG_H

#include <gtkmm/builder.h>
#include <glibmm/refptr.h>

#include "Config.h"

namespace seriesdashboard {
	class FileBrowserDialog {
	public:
		FileBrowserDialog(std::unique_ptr<Config> &c, Glib::RefPtr<Gtk::Builder> &b);

	};
}

#endif //SERIES_DASHBOARD_FILEBROWSERDIALOG_H
