#ifndef SERIES_DASHBOARD_DASHBOARD_H
#define SERIES_DASHBOARD_DASHBOARD_H

#include <glibmm/refptr.h>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/stack.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>

#include "Entry.h"
#include "Config.h"
#include "PreferencesWindow.h"

#include <vector>

namespace seriesdashboard {
	class Dashboard {
	public:
		Dashboard(int argc, char *argv[]);

		int getStatus() const;

	private:
		int status = -1;

		std::unique_ptr<seriesdashboard::Config> config;

		Glib::RefPtr<Gtk::Application> app;
		Glib::RefPtr<Gtk::Builder> builder;

		Gtk::Window *window = nullptr;
		Gtk::Stack *mainStack = nullptr;
		Gtk::Stack *dashboardStack = nullptr;

		Gtk::FileChooserDialog *fileChooserDialog = nullptr;	// TODO: Move to AddNewWindow
		std::unique_ptr<seriesdashboard::PreferencesWindow> preferences;

		std::vector<seriesdashboard::Entry> series;

		/**
		 * Set up menu button connections.
		 */
		void setupConnections() noexcept;

		/**
		 * Throw an error dialog
		 * @param message String to display as error
		 */
		void errorDialog(const std::string& message) noexcept;

		/**
		 * Create a new series entry.
		 * @param path Path of the selected folder
		 */
		void addSeries(const std::string &path);

		/**
		 * "Add new" button clicked
		 */
		void onNewClicked();
	};
}

#endif //SERIES_DASHBOARD_DASHBOARD_H
