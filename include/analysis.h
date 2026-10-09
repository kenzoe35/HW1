#pragma once

/**
 * @brief Average of one station’s row. If the station is out of range or cols ≤ 0, returns false and leaves average untouched. Otherwise sets average and returns true.
 *
 * 
 * If the station index is out of range or cols is less than or equal to 0, 
 * the function returns false and leaves the average untouched. Otherwise, 
 * it calculates the average, updates the average parameter, and returns true
 * 
 * @pre Station is not out of range or cols <= 0
 * @post Must not modify temps array
 * 
 * @param[in] temps   Pointer to the 1D flattened temperature array.
 * @param[in] rows    Total number of stations
 * @param[in] cols    Total number of days
 * @param[in] station	Refer to station array
 * @param[out] average	Reference stored temperature to calculate an average of a station
 * 
 * @return true if station is not out of range or cols <= 0
 */
bool station_average(const double* temps, int rows, int cols, int station, double& average);

/**
 * @brief Average of one day’s column across all stations. Same failure rules: day out of range or rows ≤ 0.
 *
 * If the day index is less than or equal to 0, returns false and leaves the average untouched.
 * Otherwise, it calculates the average tempreature of one day's column across all stations
 * 
 * @pre Day is not out of range
 * @post Must not modify temps array
 *
 * @param[in] temps		Pointer to the 1D flattened temperature array.
 * @param[in] rows		Total number of stations
 * @param[in] cols		Total number of days
 * @param[in] day		The 0-based day index to compute the average for.
 * @param[out] average	Reference stored temperature to calculate an average temperature for a singular day across all stations
 * 
 * @return true if successful; false if day is out of range, rows <= 0, or cols <= 0.
 */
bool day_average(const double* temps, int rows, int cols, int day, double& average);

/** @brief Finds the grid position (row, col) of the highest temperature reading.
 *
 * If rows <= 0 or cols <= 0, returns false and leaves hot_row and hot_col untouched.
 * If ties occur, the first element encountered in row-major order wins.
 *
 * @pre temps is not null.
 * @post Does not modify temps array.
 *
 * @param[in]  temps   Pointer to the 1D flattened temperature array.
 * @param[in]  rows    Total number of stations
 * @param[in]  cols    Total number of days
 * @param[out] hot_row Reference where the hottest station's row index is stored.
 * @param[out] hot_col Reference where the hottest station's day column index is stored.
 *
 * @return true if successful; false if rows <= 0 or cols <= 0.
 */
bool find_hottest(const double* temps, int rows, int cols, int& hot_row, int& hot_col);
/**
 * @brief Number of readings strictly greater than the threshold.
 *
 * Counts the readings in the temps array that are above threshold 95 degrees fahrenheit
 * 
 * @pre temps is not null
 * @post Does not modify temps array
 *
 * @param[in] temps		Pointer to the 1D flattened temperature array
 * @param[in] rows		Total number of stations
 * @param[in] cols		Total number of days
 * @param[in] threshold	The temperature required to go above
 * 
 * @return the amount of readings that are above the threshold
 */
int  count_above(const double* temps, int rows, int cols, double threshold);
