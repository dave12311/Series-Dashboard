#ifndef SERIES_DASHBOARD_CONFIG_H
#define SERIES_DASHBOARD_CONFIG_H

#include <filesystem>
#include <vector>
#include <fstream>
#include <regex>

#include "Entry.h"

#include <nlohmann/json.hpp>

#define DEFAULT_EPISODE_NUM_REGEX "((?<=\\.|\\s)\\d{2,3}(?=\\.|\\s))|((?<=S\\d\\dE)\\d\\d)|((?<=S\\d\\d(\\.|\\s)E)\\d\\d)"
#define DEFAULT_NAME_REGEX "^.+((?=S\\d\\d)|(?=\\d\\d\\.\\w+$))"

#define EPISODE_REGEX_KEY "EpisodeNumberRegex"
#define NAME_REGEX_KEY "NameRegex"
#define ENTRIES_KEY "SeriesEntries"

namespace seriesdashboard {
	class StringRegex {
	public:
		StringRegex() = default;

		StringRegex &operator=(std::string &&str);

		const std::string &getExpression() noexcept;

		const std::regex &getRegEx() noexcept;

	private:
		std::string expression;
		std::regex regex;
	};

	class Config {
	public:
		Config();

		StringRegex &getNameRegEx() noexcept;

		StringRegex &getEpisodeRegEx() noexcept;

	private:
		std::filesystem::path configPath;

		StringRegex nameRegEx, episodeRegEx;
		std::vector<Entry> series;
	};
}

#endif //SERIES_DASHBOARD_CONFIG_H
