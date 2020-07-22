#include "PreferencesWindow.h"

#include <gtkmm/textview.h>

#include <iostream>

namespace seriesdashboard {
	PreferencesWindow::PreferencesWindow(std::unique_ptr<Config> &c, Glib::RefPtr<Gtk::Builder> b) : config(c),
																									 builder(b) {
		builder->get_widget<Gtk::Dialog>("Preferences", dialog);

		dialog->add_button("Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
		dialog->add_button("Save", Gtk::ResponseType::RESPONSE_APPLY);

		nameRegExBuffer = Gtk::TextBuffer::create();
		episodeRegExBuffer = Gtk::TextBuffer::create();

		nameRegExBuffer->set_text(config->getNameRegEx());
		episodeRegExBuffer->set_text(config->getEpisodeRegEx());

		Gtk::TextView *nameRegExBox, *episodeRegExBox;
		builder->get_widget("name_regex", nameRegExBox);
		builder->get_widget("episode_regex", episodeRegExBox);

		nameRegExBox->set_buffer(nameRegExBuffer);
		episodeRegExBox->set_buffer(episodeRegExBuffer);
	}

	void PreferencesWindow::run() {
		int result = dialog->run();

		switch (result) {
			case Gtk::ResponseType::RESPONSE_CANCEL:
				dialog->close();
				break;
			case Gtk::RESPONSE_DELETE_EVENT:
				dialog->close();
				break;
			case Gtk::ResponseType::RESPONSE_APPLY:
				// TODO: Save regex to config
				dialog->close();
				break;
		}
	}
}

