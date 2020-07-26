#include "Config.h"

#include <iostream>
#include <utility>
#include <algorithm>

namespace seriesdashboard {
	StringRegex &StringRegex::operator=(std::string &&str) {
		expression = std::move(str);

		std::string escaped;
		escaped.reserve(expression.size());
		for (char i : expression) {
			if(i == '(' || i == ')') {
				escaped.push_back('\\');
			}
			escaped.push_back(i);
		}

		regex = escaped;

		return *this;
	}

	const std::string &StringRegex::getExpression() noexcept {
		return expression;
	}

	const std::regex &StringRegex::getRegEx() noexcept {
		return regex;
	}

	Config::Config() {
#ifdef __WIN32__
		// TODO: Windows path
#elif __unix__
		std::string path = getenv("HOME");
		path.append("/.seriesdashboard/config");
		configPath = path;
#endif

		// Check if config file exists
		if (!std::filesystem::exists(configPath)) {

			// Set defaults
			episodeRegEx = DEFAULT_EPISODE_NUM_REGEX;
			nameRegEx = DEFAULT_NAME_REGEX;

			// Create default config
			nlohmann::json json;

			json[EPISODE_REGEX_KEY] = DEFAULT_EPISODE_NUM_REGEX;
			json[NAME_REGEX_KEY] = DEFAULT_NAME_REGEX;
			json[ENTRIES_KEY] = nlohmann::json::array();

			// Write config to file
			std::filesystem::create_directory(configPath.parent_path());
			std::string configString = json.dump(2);
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
				nlohmann::json json;
				json = nlohmann::json::parse(config);

				if (json[EPISODE_REGEX_KEY].empty()) {
					episodeRegEx = DEFAULT_EPISODE_NUM_REGEX;
				} else {
					episodeRegEx = json[EPISODE_REGEX_KEY];
				}

				if (json[NAME_REGEX_KEY].empty()) {
					nameRegEx = DEFAULT_NAME_REGEX;
				} else {
					nameRegEx = json[NAME_REGEX_KEY];
				}

				// TODO: Parse series data
			} else {
				throw std::system_error(EIO, std::generic_category(), "Could not load config file");
			}
		}
	}

	StringRegex &Config::getNameRegEx() noexcept {
		return nameRegEx;
	}

	StringRegex &Config::getEpisodeRegEx() noexcept {
		return episodeRegEx;
	}
}
