#include <iostream>
#include <string>
using namespace std;

// Function prototype
bool isLeapYear(int year);

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

int main() {
    string input;
    int year;

    while (true) {
        cout << "Enter a year or Q to quit: ";
        cin >> input;

        if (input == "Q" || input == "q") {
            break;
        }

        try {
            year = stoi(input);

            if (year >= 1582) {
                if (isLeapYear(year)) {
                    cout << year << " is a leap year." << endl;
                }
                else {
                    cout << year << " is not a leap year." << endl;
                }
            }
            else {
                cout << "Year must be >= 1582. Please try again." << endl;
            }
        }
        catch (...) {
            cout << "Invalid input. Please enter a valid year or Q to quit." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
