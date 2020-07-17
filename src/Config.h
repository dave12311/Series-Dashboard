#ifndef SERIES_DASHBOARD_CONFIG_H
#define SERIES_DASHBOARD_CONFIG_H

#include <filesystem>
#include <vector>

#include "Entry.h"

#include <nlohmann/json.hpp>

namespace seriesdashboard {
	class Config {
	public:
		Config();

	private:
		std::filesystem::path configPath;
		nlohmann::json configJSON;

		std::vector<Entry> series;
	};
}

#endif //SERIES_DASHBOARD_CONFIG_H
