#include "analysis.h"
#include "grid.h"

bool station_average(const double* temps, int rows, int cols, int station, double& average) {
    if (temps == nullptr || rows <= 0 || cols <= 0 || station < 0 || station >= rows)
    {
        return false;
    }

    double sum = 0.0;

    for (int day = 0; day < cols; ++day)
    {
        sum += temps[grid_index(station, day, cols)];
    }
     average = sum / cols;
    return true;
}


