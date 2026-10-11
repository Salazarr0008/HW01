#ifndef ANALYSIS_H
#define ANALYSIS_H

bool station_average(const double* temps, int rows, int cols, int station, double& average);

bool day_average(const double* temps, int rows, int cols, int day, double& average);

bool find_hottest(const double* temps, int rows, int cols, int& hot_row, int& hot_col);

int count_above(const double* temps, int rows, int cols, double threshold);

#endif
