#ifndef SENSOR_H
#define SENSOR_H

typedef struct {
	char name[30];

	int NoradId;
	char Classification[2];
	char CosparId[10];
	int Epoch_Year;
	double Epoch_Day;
	double Decay_Rate1;
	double Decay_Rate2;
	double Bstar;

	double Inclination;
	double Raan;
	double Eccentricity;
	double Perigee;
	double Mean_Anomaly;
	double Mean_Motion;
	int Revolution_Number;
} SatelliteData;

int read_tle_data(const char *file_path, SatelliteData *out_data);

#endif
