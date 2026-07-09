#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sensor.h"

int read_tle_data(const char *file_path, SatelliteData *out_data) {
	FILE *fp = fopen(file_path, "r");
	if (fp == NULL) {
		return 0;
	}

	char line1[80];
	char line2[80];
	char line3[80];

	// line 2
	char NoradId_buf[10] = {0};
	char Class_buf[5] = {0};
	char CosparId_buf[15] = {0};
	char Epoch_Year_buf[5] = {0};
	char Epoch_Day_buf[15] = {0};
	char Decay_Rate1_buf[15] = {0};
	char Decay_Rate2_buf[10] = {0};
	char Bstar_buf[15] = {0};

	// line 3
	char Inclination_buf[15] = {0};
	char Raan_buf[15] = {0};
	char Eccentricity_buf[15] = {0};
	char Perigee_buf[15] = {0};
	char Mean_Anomaly_buf[15] = {0};
	char Motion_buf[15] = {0};
	char Revolution_Number_buf[10] = {0};
	
	if (fgets(line1, sizeof(line1), fp) != NULL &&
        fgets(line2, sizeof(line2), fp) != NULL &&
        fgets(line3, sizeof(line3), fp) != NULL) {

			// Satellite Name
            line1[strcspn(line1, "\r\n")] = 0;
			strncpy(out_data->name, line1, sizeof(out_data->name) -1);
			out_data->name[sizeof(out_data->name) -1] = '\0';
			
			// NORAD
			strncpy(NoradId_buf, &line2[2], 5);
			out_data->NoradId = atoi(NoradId_buf);

			// Classification
			strncpy(Class_buf, &line2[7], 1);
			strcpy(out_data->Classification, Class_buf);

			// CosparId
			strncpy(CosparId_buf, &line2[9], 8);
			strcpy(out_data->CosparId, CosparId_buf);

			// Epoch
			strncpy(Epoch_Year_buf, &line2[18], 2);
			out_data->Epoch_Year = atoi(Epoch_Year_buf);

			strncpy(Epoch_Day_buf, &line2[20], 12);
			out_data->Epoch_Day = atof(Epoch_Day_buf);

			// Decay_Rate
			strncpy(Decay_Rate1_buf, &line2[33], 10);
			out_data->Decay_Rate1 = atof(Decay_Rate1_buf);
			
			strncpy(Decay_Rate2_buf, &line2[44], 8);
			out_data->Decay_Rate2 = atof(Decay_Rate2_buf);

			// Bstar
			char bstar_mantissa[7] = {0};
			char bstar_exp[3] = {0};
			strncpy(bstar_mantissa, &line2[53], 6);
			strncpy(bstar_exp, &line2[59], 2);
			double mantissa = atof(bstar_mantissa) * 1e-5;
			double exponent = atof(bstar_exp);
			out_data->Bstar = mantissa * pow(10, exponent);

			// line 3
			// Inclination
			strncpy(Inclination_buf, &line3[8], 8);
			out_data->Inclination = atof(Inclination_buf);

			// Raan
			strncpy(Raan_buf, &line3[17], 8);
			out_data->Raan = atof(Raan_buf);

			// Eccentricity
			strncpy(Eccentricity_buf, &line3[26], 7);
			out_data->Eccentricity = atof(Eccentricity_buf) * 0.0000001;

			// Perigee
			strncpy(Perigee_buf, &line3[34], 8);
			out_data->Perigee = atof(Perigee_buf);

			// Mean_Anomaly
			strncpy(Mean_Anomaly_buf, &line3[43], 8);
			out_data->Mean_Anomaly = atof(Mean_Anomaly_buf);

			// Mean_Motion
			strncpy(Motion_buf, &line3[52], 11);
            out_data->Mean_Motion = atof(Motion_buf);

			// Revolution_Number
			strncpy(Revolution_Number_buf, &line3[63], 5);
            out_data->Revolution_Number = atoi(Revolution_Number_buf);

		fclose(fp);
		return 1;
        }
	
	fclose(fp);
	return 0;
}


