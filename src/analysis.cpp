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


bool day_average(const double* temps, int rows, int cols, int day, double& average)
{
    if (temps == nullptr || rows <= 0 || cols <= 0 || day < 0 || day >= cols)
    {
        return false;
    }
    double sum = 0.0;

    for (int station = 0; station < rows; ++station)
    {
        sum += temps[grid_index(station, day, cols)];
    }

    average = sum / rows;

    return true;

}


bool find_hottest(const double* temps, int rows, int cols, int& hot_row, int& hot_col)
{
    if (temps == nullptr || rows <= 0 || cols <= 0)
  {      return false;
    }
    double hottest = temps[grid_index(0, 0, cols)];
    hot_row = 0;
    hot_col = 0;

    for (int row = 0; row < rows; ++row){
        
        for (int col = 0; col < cols; ++col)
        {
            double current = temps[grid_index(row, col, cols)];

            if (current > hottest)
            {
                hottest = current;
                hot_row = row;
                hot_col = col;
        }
    }
}
    return true;
}
