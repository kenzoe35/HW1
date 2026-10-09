#pragma once

/**
 * @brief Prints the table shown under Expected Output. Uses station_average and find_hottest. Days are shown 1-based.
 * 
 * Displays a summary table including each station's elevation and average temperature,
 * the overall hottest reading across the dataset (converting 0-based column index to 1-based day),
 * total readings exceeding 95.0 F, and a specific station lookup result.
 * 
 * Example output:
 *	=== Weather Station Report ===
 *  Denton          642 ft   avg  93.76 F
 *  Fort Worth      653 ft   avg  94.69 F
 *  Waco            470 ft   avg  95.90 F
 *  Amarillo       3605 ft   avg  86.89 F
 *  Hottest reading: 99.3 F at Waco (day 4)
 *  Readings above 95.0 F: 9
 *  Station to look up: Waco
 *  Waco averaged 95.9 F.
 * 
 * @pre stations and temps is not null
 * @post Must not modify stations nor temps array
 *
 * @param[in] stations	Array of station structure to search
 * @param[in] temps		Pointer to the 1D flattened temperature array
 * @param[in] rows		Total number of stations
 * @param[in] cols		Total number of days
 */
void print_report(const Station* stations, const double* temps, int rows, int cols);
