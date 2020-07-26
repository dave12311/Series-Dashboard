#include "Config.h"

#include <iostream>
#include <utility>
#include <algorithm>

namespace seriesdashboard {
	StringRegex &StringRegex::operator=(std::string &&str) {

		// Add escape character before parentheses
		std::string escaped;
		escapeParentheses(str, escaped);

		try {
			regex = escaped;
			expression = std::move(str);
		} catch (std::regex_error &error) {
			throw error;
		}

		return *this;
	}

	void StringRegex::escapeParentheses(const std::string &from, std::string &to) noexcept {
		to.reserve(from.size());
		for (char i : from) {
			if (i == '(' || i == ')') {
				to.push_back('\\');
			}
			to.push_back(i);
		}
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

			// Write config to file
			std::filesystem::create_directory(configPath.parent_path());
			write();
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
					try {
						episodeRegEx = json[EPISODE_REGEX_KEY];
					} catch (std::regex_error &error) {
						std::cerr << "Invalid episode number regex in config file!\nUsing defaults...\n" << error.what()
								  << std::endl;
						episodeRegEx = DEFAULT_EPISODE_NUM_REGEX;
					}

				}

				if (json[NAME_REGEX_KEY].empty()) {
					nameRegEx = DEFAULT_NAME_REGEX;
				} else {
					try {
						nameRegEx = json[NAME_REGEX_KEY];
					} catch (std::regex_error &error) {
						std::cerr << "Invalid series name regex in config file!\nUsing defaults...\n" << error.what()
								  << std::endl;
						nameRegEx = DEFAULT_NAME_REGEX;
					}
				}

				// TODO: Parse series data
			} else {
				throw std::system_error(EIO, std::generic_category(), "Could not load config file");
			}
		}
	}

	void Config::write() {
		nlohmann::json json;

		json[EPISODE_REGEX_KEY] = episodeRegEx.getExpression();
		json[NAME_REGEX_KEY] = nameRegEx.getExpression();
		json[ENTRIES_KEY] = nlohmann::json::array();	//TODO: Convert episode entries to JSON

		// Write config to file
		std::string configString = json.dump(2);
		std::ofstream writer;
		writer.open(configPath);

		if (writer.is_open()) {
			writer << configString << std::endl << std::endl;
			writer.close();
		} else {
			throw std::system_error(EIO, std::generic_category(), "Could not create config file");
		}
	}
}
