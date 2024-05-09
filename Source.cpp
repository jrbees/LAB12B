#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Function prototypes
bool isLeapYear(int year);
int daysInMonth(int month, int year);
int dayOfWeek(int month, int day, int year);
int getMonthNumber(const string& monthName);

// Mapping of month names to their numeric representations
unordered_map<string, int> monthMap = {
    {"january", 1},
    {"february", 2},
    {"march", 3},
    {"april", 4},
    {"may", 5},
    {"june", 6},
    {"july", 7},
    {"august", 8},
    {"september", 9},
    {"october", 10},
    {"november", 11},
    {"december", 12}
};

/**
 * isLeapYear – determines whether a given year is a leap year
 * under the Gregorian calendar.
 * @param year the year; expected to be >= 1582
 * @return true if year is a leap year; false otherwise
 */
bool isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * daysInMonth – determines the number of days in a specified month
 * @param month the month; expected to be in the range [1..12]
 * @param year the year; expected to be >= 1582
 * @return number of days in the specified month for the given year
 */
int daysInMonth(int month, int year) {
    switch (month) {
    case 1:  // January
    case 3:  // March
    case 5:  // May
    case 7:  // July
    case 8:  // August
    case 10: // October
    case 12: // December
        return 31;
    case 4:  // April
    case 6:  // June
    case 9:  // September
    case 11: // November
        return 30;
    case 2:  // February
        if (isLeapYear(year)) {
            return 29;
        }
        else {
            return 28;
        }
    default:
        return -1; // Invalid month
    }
}

/**
 * dayOfWeek – Computes the weekday of a given date using Zeller's congruence.
 * @param year the year
 * @param month the month (1 = January ... 12 = December)
 * @param day the day of the month
 * @return the weekday (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
 */
int dayOfWeek(int month, int day, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int h = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;

    // Adjust h to be within 0 to 6 (0 = Saturday, 1 = Sunday, ..., 6 = Friday)
    h = (h + 5) % 7;

    return h;
}

/**
 * getMonthNumber - Converts a month name to its corresponding number.
 * @param monthName the name of the month (case-insensitive)
 * @return the numeric representation of the month (1 = January, 2 = February, ..., 12 = December)
 *         or -1 if the month name is invalid
 */
int getMonthNumber(const string& monthName) {
    string lowercaseMonth = monthName;
    transform(lowercaseMonth.begin(), lowercaseMonth.end(), lowercaseMonth.begin(), ::tolower);

    auto it = monthMap.find(lowercaseMonth);
    if (it != monthMap.end()) {
        return it->second;
    }
    else {
        return -1; // Invalid month name
    }
}

int main() {
    string input;
    int month, year;

    // Prompt for input
    cout << "Enter a month and year (e.g., March 2023) or Q to quit: ";
    getline(cin, input);

    while (input != "Q" && input != "q") {
        istringstream iss(input);
        string monthName;
        if (!(iss >> monthName >> year) || iss.peek() != EOF) {
            cout << "Invalid input. Please enter month year (e.g., March 2023)." << endl;
        }
        else {
            // Convert month name to its corresponding number
            month = getMonthNumber(monthName);

            if (month == -1) {
                cout << "Invalid month name. Please enter a valid month name (e.g., March)." << endl;
            }
            else if (year < 1582) {
                cout << "Invalid year. Please enter a valid year (>=1582)." << endl;
            }
            else {
                // Determine the number of days in the specified month and year
                int numDays = daysInMonth(month, year);
                int startDay = dayOfWeek(month, 1, year); // Starting day of the month

                // Display the calendar header
                cout << " " << monthName << " " << year << endl;
                cout << " Su Mo Tu We Th Fr Sa" << endl;

                // Create calendar layout dynamically
                int currentDay = 1;
                int weekStart = startDay;

                // Open output file
                string filename = monthName + to_string(year) + ".txt";
                ofstream outfile(filename);

                if (!outfile.is_open()) {
                    cerr << "Error: Unable to open file " << filename << " for writing." << endl;
                    break;
                }

                // Write to output file
                outfile << " " << monthName << " " << year << endl;
                outfile << " Su Mo Tu We Th Fr Sa" << endl;

                // Loop through weeks
                while (currentDay <= numDays) {
                    // Start a new week
                    string weekLine = "";

                    // Fill in days for the week
                    for (int i = 0; i < 7; ++i) {
                        if (i < weekStart) {
                            weekLine += "   "; // Empty space for days before the start day
                        }
                        else if (currentDay <= numDays) {
                            // Append current day to the week line
                            if (currentDay < 10) {
                                weekLine += " " + to_string(currentDay) + " ";
                            }
                            else {
                                weekLine += to_string(currentDay) + " ";
                            }
                            ++currentDay;
                        }
                    }

                    // Output the week line to console
                    cout << weekLine << endl;

                    // Write the week line to output file
                    outfile << weekLine << endl;

                    // Move to the next week
                    weekStart = 0; // Reset the week start for subsequent weeks
                }

                // Close the output file
                outfile.close();
                cout << "Output file: " << filename << endl;
            }
        }

        // Prompt for next input
        cout << "Enter a month and year (e.g., March 2023) or Q to quit: ";
        getline(cin, input);
    }

    return 0;
}
