#ifndef SERIES_DASHBOARD_ENTRY_H
#define SERIES_DASHBOARD_ENTRY_H

#include <filesystem>

#include "Apidata.h"

namespace seriesdashboard {
	class Entry {
	public:
		void open();

	private:
		std::filesystem::path seriesFolderPath;
		unsigned int currentEpisode;
		seriesdashboard::Apidata metadata;
	};
}

#endif //SERIES_DASHBOARD_ENTRY_H
