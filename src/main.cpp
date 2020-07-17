#include "Dashboard.h"

#include <curlpp/cURLpp.hpp>

int main(int argc, char *argv[]) {
	seriesdashboard::Dashboard dashboard(argc, argv);
	return dashboard.getStatus();
}
