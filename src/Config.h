#ifndef SERIES_DASHBOARD_CONFIG_H
#define SERIES_DASHBOARD_CONFIG_H

#include <filesystem>
#include <vector>
#include <fstream>

#include "Entry.h"

#include <nlohmann/json.hpp>

#define DEFAULT_EPISODE_NUM_REGEX "((?<=\\.|\\s)\\d{2,3}(?=\\.|\\s))|((?<=S\\d\\dE)\\d\\d)|((?<=S\\d\\d\\.E)\\d\\d)"
#define DEFAULT_NAME_REGEX "TODO: REGEX"

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
