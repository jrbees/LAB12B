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
 * @return the weekday (0 = Saturday ... 6 = Friday)
 */
int dayOfWeek(int month, int day, int year) {
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int h = (day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j)) % 7;

    // Convert h to be within 0 to 6 (0 = Saturday, 1 = Sunday, ..., 6 = Friday)
    if (h < 0) {
        h += 7;
    }

    return h;
}

int main() {
    string input;
    int month, day, year;

    // Array of weekday names
    string weekdays[7] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

    // Array of month names
    string months[12] = { "January", "February", "March", "April", "May", "June",
                         "July", "August", "September", "October", "November", "December" };

    while (true) {
        cout << "Enter a date (month day year) or Q to quit: ";
        getline(cin, input);

        if (input == "Q" || input == "q") {
            break;
        }

        istringstream iss(input);
        if (!(iss >> month >> day >> year) || iss.peek() != EOF) {
            cout << "Invalid input. Please enter month day year (e.g., 10 13 2011)." << endl;
            continue;
        }

        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year) || year < 1582) {
            cout << "Invalid date. Please enter a valid date." << endl;
            continue;
        }

        int weekdayIndex = dayOfWeek(month, day, year);
        cout << weekdays[weekdayIndex] << ", " << months[month - 1] << " " << day << ", " << year << endl;
    }

    return 0;
}
