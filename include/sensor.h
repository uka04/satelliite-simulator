#ifndef SENSOR_H
#define SENSOR_H

typedef struct {
	char name[30];
	int NoradId;
	char Classification[2];
	char CosparId[10];
	int Epoch_Year;
	double Epoch_Day;
	double mean_motion;
	double Decay_Rate1;
	double Decay_Rate2;
	double Bstar;
} SatelliteData;

int read_tle_data(const char *file_path, SatelliteData *out_data);

#endif
