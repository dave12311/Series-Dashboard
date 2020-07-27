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
		PreferencesWindow(std::unique_ptr<Config> &c, Glib::RefPtr<Gtk::Builder> &b);

		/**
		 * Open Preferences window.
		 */
		void run();

	private:
		Glib::RefPtr<Gtk::Builder> builder;
		Gtk::Dialog *dialog = nullptr;

		std::unique_ptr<Config> &config;

		Glib::RefPtr<Gtk::TextBuffer> nameRegExBuffer, episodeRegExBuffer;

		void errorMessage(std::string &&error) noexcept;

		void onSaveClicked();

		inline void onCancelClicked() noexcept { dialog->close(); }

		inline void onDefaultClicked() noexcept {
			config->setDefaults();
			nameRegExBuffer->set_text(DEFAULT_NAME_REGEX);
			episodeRegExBuffer->set_text(DEFAULT_EPISODE_NUM_REGEX);
			config->write();
		}
	};
}


#endif //SERIES_DASHBOARD_PREFERENCESWINDOW_H
