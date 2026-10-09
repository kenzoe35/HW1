#include "station.h"
#include "analysis.h"
#include "grid.h"

bool station_average(const double* temps, int rows, int cols, int station, double& average) {

	if (rows <= 0 || cols <= 0 || !in_bounds(station, 0, rows, cols)) {
		return false;
	}
	
	double sum = 0.0;

	for (int i = 0; i < cols; i++) {
		sum += temps[grid_index(station, i, cols)];
	}

	average = sum / cols;
	return true;
}


bool day_average(const double* temps, int rows, int cols, int day, double& average) {

	if (rows <= 0 || cols <= 0 || !in_bounds(0, day, rows, cols)){
		return false;
	}

	double sum = 0.0;

	for (int i = 0; i < rows; i++) {
		sum += temps[grid_index(i, day, cols)];
	}

	average = sum / rows;
	return true;
}

bool find_hottest(const double* temps, int rows, int cols, int& hot_row, int& hot_col) {
	if (rows <= 0 || cols <= 0) {
		return false;
	}

	double max_temp = temps[grid_index(0, 0, cols)];
	int max_row = 0;
	int max_column = 0;


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
		double current_temp = temps[grid_index(i, j, cols)];
			if (current_temp > max_temp) {
				max_temp = current_temp;
				max_row = i;
				max_column = j;
			}
		}
	}

	hot_row = max_row;
	hot_col = max_column;
	return true;
}

int  count_above(const double* temps, int rows, int cols, double threshold) {
	
	if (rows <= 0 || cols <= 0) {
		return 0;
	}

	int count = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (temps[grid_index(i,j, cols)] > threshold) {
				count++;
			}
		}
	}
	return count;
}
