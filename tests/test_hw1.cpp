#include <gtest/gtest.h>
#include "grid.h"
#include "analysis.h"
#include "station.h"

// ============================================================================
// 1. Grid Tests (grid_index & in_bounds)
// ============================================================================

TEST(GridTest, GridIndexAndBoundaryCheck) {
    int rows = 2;
    int cols = 3;

    // Standard index calculations on 2x3 grid
    EXPECT_EQ(grid_index(0, 0, cols), 0);
    EXPECT_EQ(grid_index(1, 2, cols), 5); // Last valid index: 1 * 3 + 2 = 5

    // Boundary Cases: Last valid vs. First invalid index
    EXPECT_TRUE(in_bounds(1, 2, rows, cols));  // Last valid (row 1, col 2)
    EXPECT_FALSE(in_bounds(1, 3, rows, cols)); // First invalid col (col 3)
    EXPECT_FALSE(in_bounds(2, 0, rows, cols)); // First invalid row (row 2)

    // Boundary Case: Negative index
    EXPECT_FALSE(in_bounds(-1, 0, rows, cols));
    EXPECT_FALSE(in_bounds(0, -1, rows, cols));

    // Boundary Case: Empty grid
    EXPECT_FALSE(in_bounds(0, 0, 0, 3));
    EXPECT_FALSE(in_bounds(0, 0, 2, 0));
}

// ============================================================================
// 2. Analysis Tests (station_average, day_average, find_hottest, count_above)
// ============================================================================

class AnalysisTest : public ::testing::Test {
protected:
    static constexpr int rows = 2;
    static constexpr int cols = 3;

    // Small 2x3 grid for hand calculations:
    // Station 0: [90.0, 95.0, 100.0] -> Avg: 95.0
    // Station 1: [80.0, 85.0,  90.0] -> Avg: 85.0
    // Days:      [Day 0, Day 1, Day 2]
    // Day 1 Avg: (95.0 + 85.0) / 2 = 90.0
    double temps[6] = {
        90.0, 95.0, 100.0,
        80.0, 85.0,  90.0
    };
};

TEST_F(AnalysisTest, StationAverageSuccessAndFailure) {
    double avg = 0.0;

    // Valid calculation
    EXPECT_TRUE(station_average(temps, rows, cols, 0, avg));
    EXPECT_DOUBLE_EQ(avg, 95.0);

    // Failure Path & Boundary: Negative index
    double sentinel = -999.0;
    EXPECT_FALSE(station_average(temps, rows, cols, -1, sentinel));
    EXPECT_DOUBLE_EQ(sentinel, -999.0); // Verify out-parameter left alone

    // Failure Path & Boundary: First invalid station index (index 2 for 2 rows)
    EXPECT_FALSE(station_average(temps, rows, cols, 2, sentinel));
    EXPECT_DOUBLE_EQ(sentinel, -999.0); // Verify out-parameter left alone

    // Failure Path & Boundary: Empty grid
    EXPECT_FALSE(station_average(temps, 0, cols, 0, sentinel));
    EXPECT_DOUBLE_EQ(sentinel, -999.0); // Verify out-parameter left alone
}

TEST_F(AnalysisTest, DayAverageSuccessAndFailure) {
    double avg = 0.0;

    // Valid calculation for Day 1
    EXPECT_TRUE(day_average(temps, rows, cols, 1, avg));
    EXPECT_DOUBLE_EQ(avg, 90.0);

    // Failure Path & Boundary: Invalid day index (first invalid = 3)
    double sentinel = 123.45;
    EXPECT_FALSE(day_average(temps, rows, cols, 3, sentinel));
    EXPECT_DOUBLE_EQ(sentinel, 123.45); // Verify out-parameter left alone
}

TEST_F(AnalysisTest, FindHottestSuccessAndEmptyGrid) {
    int hot_row = -1;
    int hot_col = -1;

    // Hottest is 100.0 at Station 0, Day 2 (row 0, col 2)
    EXPECT_TRUE(find_hottest(temps, rows, cols, hot_row, hot_col));
    EXPECT_EQ(hot_row, 0);
    EXPECT_EQ(hot_col, 2);

    // Failure Path & Boundary: Empty grid
    EXPECT_FALSE(find_hottest(temps, 0, 0, hot_row, hot_col));
}

TEST_F(AnalysisTest, FindHottestTieBreaker) {
    // Boundary Case: Tie for hottest reading (Row-major tiebreaking)
    double tie_temps[4] = {
        99.0, 80.0, // Row 0
        99.0, 70.0  // Row 1
    };
    int hot_row = -1;
    int hot_col = -1;

    // First max occurrence in row-major order is (row 0, col 0)
    EXPECT_TRUE(find_hottest(tie_temps, 2, 2, hot_row, hot_col));
    EXPECT_EQ(hot_row, 0);
    EXPECT_EQ(hot_col, 0);
}

TEST_F(AnalysisTest, CountAboveSuccess) {
    // Temps strictly above 90.0 in {90.0, 95.0, 100.0, 80.0, 85.0, 90.0} are 95.0 and 100.0
    EXPECT_EQ(count_above(temps, rows, cols, 90.0), 2);

    // Boundary Case: Empty grid
    EXPECT_EQ(count_above(temps, 0, 0, 90.0), 0);
}

// ============================================================================
// 3. Station Tests (find_station)
// ============================================================================

TEST(StationTest, FindStationMatchAndNotFound) {
    Station stations[2] = {
        {"Denton", 642.0},
        {"Waco", 470.0}
    };

    // Valid lookup
    const Station* match = find_station(stations, 2, "Waco");
    ASSERT_NE(match, nullptr);
    EXPECT_EQ(match->name, "Waco");
    EXPECT_DOUBLE_EQ(match->elevation_ft, 470.0);

    // Boundary Case: Name that is not found
    EXPECT_EQ(find_station(stations, 2, "Austin"), nullptr);

    // Boundary Case: Empty list / count = 0
    EXPECT_EQ(find_station(stations, 0, "Denton"), nullptr);
}
