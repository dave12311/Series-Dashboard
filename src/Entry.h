#ifndef SERIES_DASHBOARD_ENTRY_H
#define SERIES_DASHBOARD_ENTRY_H

#include <filesystem>

#include "Apidata.h"

namespace seriesdashboard {
	class Entry {
	public:

		Entry(const std::string &path);

		/**
		 * Open next episode in default media player.
		 */
		void open();

	private:
		std::string name;
		std::filesystem::path folderPath;
		unsigned int nextEpisode;
		seriesdashboard::Apidata metadata;
	};
}

#endif //SERIES_DASHBOARD_ENTRY_H
