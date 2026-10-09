#include <iostream>
#include <iomanip>
#include "analysis.h"
#include "station.h"
#include "report.h"
#include "grid.h"

int main() {
	constexpr int station_count = 4;
	constexpr int day_count = 7;

    	const Station stations[station_count] = {
        	{"Denton", 642.0},
        	{"Fort Worth", 653.0},
        	{"Waco", 470.0},
        	{"Amarillo", 3605.0},
    	};

    	// Row = station, column = day. Stored flat: 
    	// the reading for station s on day d is temps[s * day_count + d].
    	const double temps[station_count * day_count] = {
        	91.2, 93.5, 95.0, 97.8, 96.1, 92.4, 90.3,   // Denton
        	92.0, 94.1, 96.4, 98.6, 97.2, 93.0, 91.5,   // Fort Worth
        	93.4, 95.2, 97.9, 99.3, 98.1, 94.6, 92.8,   // Waco
        	84.5, 86.0, 88.2, 90.7, 89.9, 85.3, 83.6,   // Amarillo
    	};

    	print_report(stations, temps, station_count, day_count);

    	int above_count = count_above(temps, station_count, day_count, 95.0);
    	std::cout << "Readings above 95.0 F: " << above_count << "\n";

    	std::cout << "Station to look up: ";
    	std::string target_name;
    	std::getline(std::cin, target_name);

    	const Station* match = find_station(stations, station_count, target_name);

    	if (match != nullptr) {
        	int row_index = match - stations;
        	double lookup_average = 0.0;
        	if (station_average(temps, station_count, day_count, row_index, lookup_average)) {
            		std::cout << target_name << " averaged " << std::fixed << std::setprecision(1) << lookup_average << " F.\n";
        	}
    	}
     	else {
        	std::cout << "No station named: " << target_name << "\n";
     	}
    	return 0;
}
