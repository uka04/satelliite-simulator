#include <stdlib.h>
#include <time.h>

int get_temperature() {
	srand(time(NULL));

	int temp = (rand() % 15) + 21;

	return temp;
}

int get_battery(void) {
	srand(time(NULL));

	int battery = (rand() % 100) + 1;

	return battery;
}
