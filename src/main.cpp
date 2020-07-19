#include "Dashboard.h"

int main(int argc, char *argv[]) {
	seriesdashboard::Dashboard dashboard(argc, argv);
	return dashboard.getStatus();
}
