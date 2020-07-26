#include "PreferencesWindow.h"

#include <gtkmm/textview.h>
#include <gtkmm/messagedialog.h>

namespace seriesdashboard {
	PreferencesWindow::PreferencesWindow(std::unique_ptr<Config> &c, Glib::RefPtr<Gtk::Builder> &b) : config(c),
																									  builder(b) {
		builder->get_widget<Gtk::Dialog>("Preferences", dialog);

		Gtk::Button *defaultButton, *cancelButton, *saveButton;

		builder->get_widget<Gtk::Button>("pref_default", defaultButton);
		builder->get_widget<Gtk::Button>("pref_cancel", cancelButton);
		builder->get_widget<Gtk::Button>("pref_save", saveButton);

		defaultButton->signal_clicked().connect(sigc::mem_fun(this, &PreferencesWindow::onDefaultClicked));
		cancelButton->signal_clicked().connect(sigc::mem_fun(this, &PreferencesWindow::onCancelClicked));
		saveButton->signal_clicked().connect(sigc::mem_fun(this, &PreferencesWindow::onSaveClicked));

		nameRegExBuffer = Gtk::TextBuffer::create();
		episodeRegExBuffer = Gtk::TextBuffer::create();

		nameRegExBuffer->set_text(config->getNameRegEx().getExpression());
		episodeRegExBuffer->set_text(config->getEpisodeRegEx().getExpression());

		Gtk::TextView *nameRegExBox, *episodeRegExBox;
		builder->get_widget("name_regex", nameRegExBox);
		builder->get_widget("episode_regex", episodeRegExBox);

		nameRegExBox->set_buffer(nameRegExBuffer);
		episodeRegExBox->set_buffer(episodeRegExBuffer);
	}

	void PreferencesWindow::run() {
		int result = dialog->run();
		if (result == Gtk::ResponseType::RESPONSE_DELETE_EVENT) {
			dialog->close();
		}
	}

	void PreferencesWindow::errorMessage(std::string &&error) noexcept {
		Gtk::MessageDialog errorDialog(error);
		errorDialog.set_title("RegEx Error");
		errorDialog.run();
		errorDialog.close();
		dialog->present();
	}

	void PreferencesWindow::onSaveClicked() {
		if (nameRegExBuffer->get_text() != config->getNameRegEx().getExpression()) {
			if (!config->setNameRegEx(nameRegExBuffer->get_text())) {
				errorMessage("Incorrect series name RegEx!");
			} else {
				config->write();
				dialog->close();
			}
		} else if (episodeRegExBuffer->get_text() != config->getEpisodeRegEx().getExpression()) {
			if (!config->setEpisodeRegEx(episodeRegExBuffer->get_text())) {
				errorMessage("Incorrect episode number RegEx!");
			} else {
				config->write();
				dialog->close();
			}
		} else {
			dialog->close();
		}
	}

	void PreferencesWindow::onDefaultClicked() {

	}
}

