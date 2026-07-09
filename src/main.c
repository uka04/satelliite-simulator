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
	
	char line1[80];
	char line2[80];
	char line3[80];
	char time_str[30];

	get_current_time_str(time_str, sizeof(time_str));	
	
	SatelliteData my_satellite;

	if (read_tle_data("data/iss.tle", &my_satellite)) {
        printf("[%s]\n", time_str);
        printf("==== Satellite Control Simulator ====\n");
        printf("Satellite Name : %s\n\n", my_satellite.name);

		// line 2
		printf("-- Line 2 Info --\n");
		printf("Norad Id       : %d\n", my_satellite.NoradId);
		printf("Classification : %s\n", my_satellite.Classification);
		printf("CosparId       : %s\n", my_satellite.CosparId);
		printf("Epoch_Year     : %d\n", my_satellite.Epoch_Year);
		printf("Epoch_Day      : %f\n", my_satellite.Epoch_Day);
		printf("Decay Rate1    : %f\n", my_satellite.Decay_Rate1);
		printf("Decay Rate2    : %f\n", my_satellite.Decay_Rate2);
		printf("Bstar          : %.8f\n\n", my_satellite.Bstar);

		// line 3
		printf("-- Line 3 Info --\n");
		printf("Inclination       : %.4f\n", my_satellite.Inclination);
		printf("Raan              : %.4f\n", my_satellite.Raan);
		printf("Eccentricity      : %.7f\n", my_satellite.Eccentricity);
		printf("Perigee           : %.4f\n", my_satellite.Perigee);
		printf("Mean_Anomaly      : %.4f\n", my_satellite.Mean_Anomaly);
        printf("Mean_Motion       : %.2f orbits/day\n", my_satellite.Mean_Motion);
		printf("Revolution_Number : %d\n", my_satellite.Revolution_Number);
        
        fprintf(log_file, "[%s]\n", time_str);
        fprintf(log_file, "==== Satellite Control Simulator ====\n");
        fprintf(log_file, "Satellite Name : %s\n\n", my_satellite.name);

		// line 2
		fprintf(log_file, "-- Line 2 Info --\n");
		fprintf(log_file, "Norad Id       : %d\n", my_satellite.NoradId);
		fprintf(log_file, "Classification : %s\n", my_satellite.Classification);
		fprintf(log_file, "CosparId       : %s\n", my_satellite.CosparId);
		fprintf(log_file, "Epoch_Year     : %d\n", my_satellite.Epoch_Year);
		fprintf(log_file, "Epoch_Day      : %f\n", my_satellite.Epoch_Day);
		fprintf(log_file, "Decay Rate1    : %f\n", my_satellite.Decay_Rate1);
		fprintf(log_file, "Decay Rate2    : %f\n", my_satellite.Decay_Rate2);
		fprintf(log_file, "Bstar          : %.8f\n\n", my_satellite.Bstar);

		// line 3
		fprintf(log_file, "-- Line 3 Info --\n");
		fprintf(log_file, "Inclination       : %.4f\n", my_satellite.Inclination);
		fprintf(log_file, "Raan              : %.4f\n", my_satellite.Raan);
		fprintf(log_file, "Eccentricity      : %.7f\n", my_satellite.Eccentricity);
		fprintf(log_file, "Perigee           : %.4f\n", my_satellite.Perigee);
		fprintf(log_file, "Mean_Anomaly      : %.4f\n", my_satellite.Mean_Anomaly);
        fprintf(log_file, "Mean_motion       : %.2f orbits/day\n", my_satellite.Mean_Motion);
		fprintf(log_file, "Revolution_Number : %d\n", my_satellite.Revolution_Number);
        fprintf(log_file, "------------------------------------\n");
    } else {
        printf("Error: Failed to read satellite data.\n");
    }

	fclose(log_file);

	return 0;
}
