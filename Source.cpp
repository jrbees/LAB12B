#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Function prototypes
bool isLeapYear(int year);
int daysInMonth(int month, int year);
int dayOfWeek(int month, int day, int year);

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

    return h+1;
}

int main() {
    string input;
    int month, year;

    // Prompt for input
    cout << "Enter a month and year (e.g., 1 2024) or Q to quit: ";
    getline(cin, input);

    while (input != "Q" && input != "q") {
        istringstream iss(input);
        if (!(iss >> month >> year) || iss.peek() != EOF) {
            cout << "Invalid input. Please enter month year (e.g., 1 2024)." << endl;
        }
        else if (month < 1 || month > 12 || year < 1582) {
            cout << "Invalid month or year. Please enter a valid month (1-12) and year (>=1582)." << endl;
        }
        else {
            // Determine the number of days in the specified month and year
            int numDays = daysInMonth(month, year);
            int startDay = dayOfWeek(month, 1, year); // Starting day of the month

            // Display the calendar header
            cout << " " << month << " " << year << endl;
            cout << " Su Mo Tu We Th Fr Sa" << endl;

            // Create calendar layout dynamically
            int currentDay = 1;
            int weekStart = startDay;

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

                // Output the week line
                cout << weekLine << endl;

                // Move to the next week
                weekStart = 0; // Reset the week start for subsequent weeks
            }
        }

        // Prompt for next input
        cout << "Enter a month and year (e.g., 1 2024) or Q to quit: ";
        getline(cin, input);
    }

    return 0;
}
