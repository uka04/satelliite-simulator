#include <stdio.h>
#include <time.h>
#include "sensor.h"

void get_current_time_str(char *buffer, int max_size) {
	time_t raw_time = time(NULL);
	struct tm *time_info = localtime(&raw_time);

	strftime(buffer, max_size, "%Y-%m-%d %H:%M:%S", time_info);
}

int main() {

	FILE *log_file = fopen("logs/satellite.log", "a");
	if (log_file == NULL) {
		printf("can't open the log file");
		return 1;
	}
		
	int temp = get_temperature();
	int battery = get_battery();
	char time_str[30];

	get_current_time_str(time_str, sizeof(time_str));
	
	printf("[%s]\n", time_str);
	printf("==== Satellite Control Simulator ====\n");
	printf("Temperature : %d C\n", temp);
	printf("Battery     : %d %%\n", battery);
	printf("Voltage     : 4.10 V\n");
	printf("Mode        : NORMAL\n");	
	
	fprintf(log_file, "[%s]\n", time_str);
	fprintf(log_file, "==== Satellite Control Simulator ===\n");
	fprintf(log_file, "Temperature : %d C\n", temp);
	fprintf(log_file, "Battery     : %d %%\n", battery);
	fprintf(log_file, "------------------------------------\n");

	fclose(log_file);
	
	return 0;
}
