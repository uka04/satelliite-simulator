#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	char NoradId_buf[10];
	char Class_buf[2];
	char CosparId_buf[10];
	char Epoch_Year_buf[3];
	char Epoch_Day_buf[13];
	char Decay_Rate1_buf[11];
	char Decay_Rate2_buf[9];
	char Bstar_buf[9];

	// line 3
	char motion_buf[12];
	
	if (fgets(line1, sizeof(line1), fp) != NULL &&
        fgets(line2, sizeof(line2), fp) != NULL &&
        fgets(line3, sizeof(line3), fp) != NULL) {

			// Satellite Name
            line1[strcspn(line1, "\r\n")] = 0;
			strncpy(out_data->name, line1, sizeof(out_data->name) -1);
			out_data->name[sizeof(out_data->name) -1] = '\0';
			
			// NORAD
			strncpy(NoradId_buf, &line2[2], 5);
			NoradId_buf[9] = '\0';
			out_data->NoradId = atoi(NoradId_buf);

			// Classification
			strncpy(Class_buf, &line2[7], 1);
			Class_buf[1] = '\0';
			strcpy(out_data->Classification, Class_buf);

			// CosparId
			strncpy(CosparId_buf, &line2[9], 8);
			strcpy(out_data->CosparId, CosparId_buf);
			out_data->CosparId[sizeof(out_data->CosparId) -1] = '\0';

			// Epoch
			strncpy(Epoch_Year_buf, &line2[18], 2);
			Epoch_Year_buf[2] = '\0';
			out_data->Epoch_Year = atoi(Epoch_Year_buf);

			strncpy(Epoch_Day_buf, &line2[20], 12);
			Epoch_Day_buf[12] = '\0';
			out_data->Epoch_Day = atof(Epoch_Day_buf);

			// Decay_Rate
			strncpy(Decay_Rate1_buf, &line2[33], 10);
			Decay_Rate1_buf[10] = '\0';
			out_data->Decay_Rate1 = atof(Decay_Rate1_buf);
			
			strncpy(Decay_Rate2_buf, &line2[44], 8);
			Decay_Rate2_buf[8] = '\0';
			out_data->Decay_Rate2 = atof(Decay_Rate2_buf);

			// Bstar
			strncpy(Bstar_buf, &line2[53], 8);
			Bstar_buf[8] = '\0';
			out_data->Bstar = atof(Bstar_buf);

			// Mean-Motion
            strncpy(motion_buf, &line3[52], 11);
            motion_buf[11] = '\0';
            out_data->mean_motion = atof(motion_buf);

		fclose(fp);
		return 1;
        }
	
	fclose(fp);
	return 0;
}


