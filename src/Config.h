#ifndef SERIES_DASHBOARD_CONFIG_H
#define SERIES_DASHBOARD_CONFIG_H

#include <filesystem>
#include <vector>
#include <fstream>
#include <regex>

#include "Entry.h"

#include <iostream>

#include <nlohmann/json.hpp>

namespace seriesdashboard {

	// Default RegEx expressions
#define DEFAULT_EPISODE_NUM_REGEX "((?<=\\.|\\s)\\d{2,3}(?=\\.|\\s))|((?<=S\\d\\dE)\\d\\d)|((?<=S\\d\\d(\\.|\\s)E)\\d\\d)"
#define DEFAULT_NAME_REGEX "^.+((?=S\\d\\d)|(?=\\d\\d\\.\\w+$))"

	// Keys used in JSON config file
#define EPISODE_REGEX_KEY "EpisodeNumberRegex"
#define NAME_REGEX_KEY "NameRegex"
#define ENTRIES_KEY "SeriesEntries"

	class StringRegex {
	public:
		StringRegex() = default;

		StringRegex &operator=(std::string &&str);

		/**
		 * Get the RegEx expression string without the escaped parentheses.
		 * @return String reference to the expression
		 */
		[[nodiscard]] inline const std::string &getExpression() const noexcept { return expression; }

		/**
		 * Get the RegEx object.
		 * @return Reference to the RegEx object
		 */
		[[nodiscard]] inline const std::regex &getRegEx() const noexcept { return regex; }

		/**
		 * Escape '(' and ')' characters in string with '\\'.
		 * @param from String to escape
		 * @param to String to build result to
		 */
		static void escapeParentheses(const std::string &from, std::string &to) noexcept;

	private:
		std::string expression;
		std::regex regex;
	};

	class Config {
	public:
		Config();

		/**
		 * Get the combined RegEx + String object for series names.
		 * @return Reference to the StringRegex object
		 */
		[[nodiscard]] inline StringRegex &getNameRegEx() noexcept { return nameRegEx; }

		/**
		 * Set the RegEx expression for the series names.
		 * @param ex RegEx expression string
		 * @return True if successful
		 */
		inline bool setNameRegEx(std::string &&ex) { return setRegEx(std::move(ex), nameRegEx); }

		/**
		 * Get the combined RegEx + String object for episode numbers.
		 * @return Reference to the StringRegex object
		 */
		[[nodiscard]] inline StringRegex &getEpisodeRegEx() noexcept { return episodeRegEx; }

		/**
		 * Set the RegEx expressions for the episode numbers.
		 * @param ex RegEx expression string
		 * @return True if successful
		 */
		inline bool setEpisodeRegEx(std::string &&ex) noexcept { return setRegEx(std::move(ex), episodeRegEx); }

		/**
		 * Write the current configuration to the config file.
		 */
		void write();

		inline void setDefaults() noexcept {
			episodeRegEx = DEFAULT_EPISODE_NUM_REGEX;
			nameRegEx = DEFAULT_NAME_REGEX;
		};

	private:
		std::filesystem::path configPath;

		StringRegex nameRegEx, episodeRegEx;
		std::vector<Entry> series;

		inline static bool setRegEx(std::string &&ex, StringRegex &object) noexcept {
			try {
				object = std::move(ex);
				return true;
			} catch (std::regex_error &error) {
				std::cerr << error.what() << std::endl;
				return false;
			}
		}
	};
}

#endif //SERIES_DASHBOARD_CONFIG_H
