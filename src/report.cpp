#include <iostream>
#include <iomanip>
#include <string>
#include "station.h"
#include "grid.h"
#include "report.h"
#include "analysis.h"

void print_report(const Station* stations, const double* temps, int rows, int cols) {
	
	std::cout << "=== Weather Station Report ===\n";
    	std::cout << std::fixed;

    	for (int i = 0; i < rows; i++) {
        	double avg = 0.0;
        	if (station_average(temps, rows, cols, i, avg)) {
            	std::cout << std::left << std::setw(16) << stations[i].name
            	<< std::right << std::setw(6) << std::setprecision(1) << stations[i].elevation_ft << " ft   "
            	<< "avg  " << std::setprecision(2) << std::setw(6) << avg << " F\n";
        	}
    	}
    	int hot_row = 0;
    	int hot_col = 0;

    	if (find_hottest(temps, rows, cols, hot_row, hot_col)) {
        	double hottest_temp = temps[grid_index(hot_row, hot_col, cols)];
        	std::cout << "Hottest reading: " << std::fixed << std::setprecision(1) << hottest_temp
                  	<< " F at " << stations[hot_row].name
                  	<< " (day " << (hot_col + 1) << ")\n";
    	}

}
