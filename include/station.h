#pragma once
#include <string>

struct Station {
    std::string name;
    double elevation_ft;
};
/** @brief Searches for a station by name and returns a pointer to the matching station.
 *
 * Performs a case-sensitive exact match search through the stations array.
 *
 * @pre stations is not null.
 * @post Does not modify the stations array or its elements.
 *
 * @param[in] stations Array of Station structures to search.
 * @param[in] count    Total number of stations in the array.
 * @param[in] name     Station name to search for (case-sensitive).
 *
 * @return Pointer to the first matching Station if found; nullptr if not found or if count <= 0.
 */
const Station* find_station(const Station* stations, int count, const std::string& name);
