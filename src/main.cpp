#include "SeriesDashboard.h"

#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>

int main(int argc, char *argv[]) {
	SeriesDashboard dashboard(argc, argv);
	return dashboard.status;
}
