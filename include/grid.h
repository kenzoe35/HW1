#pragma once
/** @brief Computes the 1D flattened index for a 2D grid position (row, col).
 *
 * @pre row >= 0, col >= 0, col < cols, and cols > 0.
 * @post Does not modify any input parameters.
 *
 * @param[in] row  The 0-based row index.
 * @param[in] col  The 0-based column index.
 * @param[in] cols The total number of columns in each row.
 *
 * @return The calculated 1D array index (row * cols + col).
 */
int grid_index(int row, int col, int cols);


/** @brief Checks if a given (row, col) coordinate is valid within grid dimensions.
 *
 * @pre None (safely handles any integer inputs).
 * @post Does not modify any input parameters.
 *
 * @param[in] row  The row index to check.
 * @param[in] col  The column index to check.
 * @param[in] rows Total number of rows in the grid.
 * @param[in] cols Total number of columns in the grid.
 *
 * @return True if 0 <= row < rows and 0 <= col < cols; false otherwise.
 */
bool in_bounds(int row, int col, int rows, int cols);
