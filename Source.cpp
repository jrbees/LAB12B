#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Function prototypes
bool isLeapYear(int year);
int daysInMonth(int month, int year);

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

int main() {
    string input;
    int month, year;

    // Array of month names (index 0 corresponds to January, index 11 corresponds to December)
    string monthNames[12] = { "January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December" };

    while (true) {
        cout << "Enter a month and year (e.g., 1 2024) or Q to quit: ";
        getline(cin, input);

        if (input == "Q" || input == "q") {
            break;
        }

        istringstream iss(input);
        if (!(iss >> month >> year) || iss.peek() != EOF) {
            cout << "Invalid input. Please enter both month and year." << endl;
            continue;
        }

        if (month < 1 || month > 12) {
            cout << "Month must be between 1 and 12. Please try again." << endl;
            continue;
        }

        if (year < 1582) {
            cout << "Year must be >= 1582. Please try again." << endl;
            continue;
        }

        int numDays = daysInMonth(month, year);
        if (numDays == -1) {
            cout << "Invalid month. Please enter a valid month (1-12)." << endl;
        }
        else {
            cout << monthNames[month - 1] << " " << year << " has " << numDays << " days." << endl;
        }
    }

    return 0;
}
