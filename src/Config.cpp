#include "Config.h"

#include <iostream>
#include <sstream>

seriesdashboard::Config::Config() {
#ifdef __WIN32__
	// TODO: Windows path
#elif __unix__
	std::string path = getenv("HOME");
	path.append("/.seriesdashboard/config");
	configPath = path;
#endif

	// Check if config file exists
	if (!std::filesystem::exists(configPath)) {

		// Create default config
		configJSON["EpisodeNumberRegex"] = DEFAULT_EPISODE_NUM_REGEX;
		configJSON["SeriesNameRegex"] = DEFAULT_NAME_REGEX;
		configJSON["SeriesEntries"] = nlohmann::json::array();

		// Write config to file
		std::filesystem::create_directory(configPath.parent_path());
		std::string configString = configJSON.dump(2);
		std::ofstream writer;
		writer.open(configPath);

		if (writer.is_open()) {
			writer << configString << std::endl << std::endl;
			writer.close();
		} else {
			throw std::system_error(EIO, std::generic_category(), "Could not create config file");
		}
	} else {
		// Read config file
		std::ifstream reader;
		reader.open(configPath);

		if (reader.is_open()) {
			std::string config((std::istreambuf_iterator<char>(reader)), (std::istreambuf_iterator<char>()));
			configJSON = nlohmann::json::parse(config);
		} else {
			throw std::system_error(EIO, std::generic_category(), "Could not load config file");
		}
	}
}