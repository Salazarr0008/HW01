#include <gtest/gtest.h>
#include "grid.h"
#include "station.h"
#include "analysis.h"

TEST(GridIndex, ConvertsRowAndColumn)
{
    EXPECT_EQ(grid_index(0, 0, 3), 0);
    EXPECT_EQ(grid_index(1, 2, 3), 5);
}

TEST(InBounds, LastValidAndFirstInvalid)
{
    EXPECT_TRUE(in_bounds(1, 2, 2, 3));
    EXPECT_FALSE(in_bounds(2, 2, 2, 3));
    EXPECT_FALSE(in_bounds(1, 3, 2, 3));
}

TEST(InBounds, NegativeIndexAndEmptyGrid)
{
    EXPECT_FALSE(in_bounds(-1, 0, 2, 3));
    EXPECT_FALSE(in_bounds(0, -1, 2, 3));
    EXPECT_FALSE(in_bounds(0, 0, 0, 3));
    EXPECT_FALSE(in_bounds(0, 0, 2, 0));
}

TEST(StationAverage, AveragesSelectedRow)
{
    const double temps[] = {10, 20, 30, 40, 50, 60};
    double average = -1;

    EXPECT_TRUE(station_average(temps, 2, 3, 1, average));
    EXPECT_DOUBLE_EQ(average, 50.0);
}

TEST(StationAverage, InvalidInputsLeaveOutputUnchanged)
{
    const double temps[] = {10, 20, 30, 40, 50, 60};
    double average = 123.0;

    EXPECT_FALSE(station_average(temps, 2, 3, 2, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(station_average(temps, 2, 3, -1, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(station_average(nullptr, 2, 3, 0, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(station_average(temps, 0, 3, 0, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(station_average(temps, 2, 0, 0, average));
    EXPECT_DOUBLE_EQ(average, 123.0);
}

TEST(DayAverage, AveragesSelectedColumn)
{
    const double temps[] = {10, 20, 30, 40, 50, 60};
    double average = -1;

    EXPECT_TRUE(day_average(temps, 2, 3, 2, average));
    EXPECT_DOUBLE_EQ(average, 45.0);
}

TEST(DayAverage, InvalidInputsLeaveOutputUnchanged)
{
    const double temps[] = {10, 20, 30, 40, 50, 60};
    double average = 123.0;

    EXPECT_FALSE(day_average(temps, 2, 3, 3, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(day_average(temps, 2, 3, -1, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(day_average(nullptr, 2, 3, 0, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(day_average(temps, 0, 3, 0, average));
    EXPECT_DOUBLE_EQ(average, 123.0);

    EXPECT_FALSE(day_average(temps, 2, 0, 0, average));
    EXPECT_DOUBLE_EQ(average, 123.0);
}

TEST(FindHottest, FindsMaximumWithNegativeReadings)
{
    const double temps[] = {-10, -20, -30, -40, -5, -60};
    int row = -1;
    int col = -1;

    EXPECT_TRUE(find_hottest(temps, 2, 3, row, col));
    EXPECT_EQ(row, 1);
    EXPECT_EQ(col, 1);
}

TEST(FindHottest, TieKeepsFirstOccurrence)
{
    const double temps[] = {10, 50, 30, 50, 20, 40};
    int row = -1;
    int col = -1;

    EXPECT_TRUE(find_hottest(temps, 2, 3, row, col));
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 1);
}

TEST(FindHottest, InvalidInputsLeaveOutputsUnchanged)
{
    const double temps[] = {10, 20, 30};
    int row = 7;
    int col = 8;

    EXPECT_FALSE(find_hottest(nullptr, 1, 3, row, col));
    EXPECT_EQ(row, 7);
    EXPECT_EQ(col, 8);

    EXPECT_FALSE(find_hottest(temps, 0, 3, row, col));
    EXPECT_EQ(row, 7);
    EXPECT_EQ(col, 8);

    EXPECT_FALSE(find_hottest(temps, 1, 0, row, col));
    EXPECT_EQ(row, 7);
    EXPECT_EQ(col, 8);
}

TEST(CountAbove, ExcludesReadingsEqualToThreshold)
{
    const double temps[] = {10, 20, 30, 40, 50, 60};

    EXPECT_EQ(count_above(temps, 2, 3, 30.0), 3);
    EXPECT_EQ(count_above(temps, 2, 3, 60.0), 0);
}

TEST(CountAbove, InvalidInputsReturnZero)
{
    const double temps[] = {10, 20, 30};

    EXPECT_EQ(count_above(nullptr, 1, 3, 0.0), 0);
    EXPECT_EQ(count_above(temps, 0, 3, 0.0), 0);
    EXPECT_EQ(count_above(temps, 1, 0, 0.0), 0);
}

TEST(FindStation, ReturnsMatchingAddress)
{
    const Station stations[] = {
        {"Denton", 642.0},
        {"Fort Worth", 653.0}
    };

    EXPECT_EQ(find_station(stations, 2, "Fort Worth"), &stations[1]);
}

TEST(FindStation, MissingNameAndEmptyArray)
{
    const Station stations[] = {
        {"Denton", 642.0},
        {"Fort Worth", 653.0}
    };

    EXPECT_EQ(find_station(stations, 2, "Waco"), nullptr);
    EXPECT_EQ(find_station(stations, 2, "denton"), nullptr);
    EXPECT_EQ(find_station(stations, 0, "Denton"), nullptr);
}
