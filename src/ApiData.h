#ifndef SERIES_DASHBOARD_APIDATA_H
#define SERIES_DASHBOARD_APIDATA_H

#include <string>

namespace seriesdashboard {
	class ApiData {
	public:

	private:
		unsigned int id;
		std::string genres;
		std::string rating;
		std::string network;
		std::string premiered;
	};
}

#endif //SERIES_DASHBOARD_APIDATA_H
