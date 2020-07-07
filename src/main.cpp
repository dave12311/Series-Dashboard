#include "seriesDashboard.h"

#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>

int main(int argc, char *argv[]) {
	seriesDashboard dashboard(argc, argv);
	return dashboard.status;
}
