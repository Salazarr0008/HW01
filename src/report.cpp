#include "report.h"
#include "analysis.h"
#include "grid.h"
#include <iostream>
#include <iomanip>

void print_report(const Station* stations, const double* temps, int rows, int cols)
{
    std::cout << "=== Weather Station Report ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

  for (int station = 0; station < rows; ++station){
        double average = 0.0;
        station_average(temps, rows, cols, station, average);
        std::cout << std::left << std::setw(14) << stations[station].name
                  << std::right << std::setw(5) << std::setprecision(0)
                  << stations[station].elevation_ft
                  << " ft   avg " << std::setw(6) << std::setprecision(2)
                  << average << " F" << std::endl; 
  }
    int hot_row = 0;
    int hot_col = 0;

  if (find_hottest(temps, rows, cols, hot_row, hot_col)){
        std::cout << std::setprecision(1)
                  << "Hottest reading: "
                  << temps[grid_index(hot_row, hot_col, cols)]
                  << " F at " << stations[hot_row].name
                  << " (day " << hot_col + 1 << ")" << std::endl;}

    std::cout << "Readings above 95.0 F: "
              << count_above(temps, rows, cols, 95.0)
              << std::endl;
}
