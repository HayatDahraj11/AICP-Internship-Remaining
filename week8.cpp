#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int BOAT_COUNT = 10;
const int OPEN_TIME = 10;
const int CLOSE_TIME = 17;
const double FULL_HOUR_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;

struct Boat {
    int boatNumber;
    double moneyTakenToday;
    int hoursHiredToday;
    int returnTime;
};

// Function prototypes
void initializeBoats(vector<Boat>& boats);
void hireBoat(Boat& boat);
bool isAvailable(const Boat& boat, int currentTime);
void findNextAvailableBoat(const vector<Boat>& boats, int currentTime);
void endOfDayReport(const vector<Boat>& boats);

int main() {
    vector<Boat> boats(BOAT_COUNT);
    initializeBoats(boats);
    int currentTime = OPEN_TIME; // This can be set to the current time in a real-world scenario

    // TASK 1 - calculate the money taken in a day for one boat
    for (Boat& boat : boats) {
        hireBoat(boat); // Simulate hiring each boat
    }

    // TASK 2 - find the next boat available
    findNextAvailableBoat(boats, currentTime);

    // TASK 3 - calculate the money taken for all the boats at the end of the day
    endOfDayReport(boats);

    return 0;
}

void initializeBoats(vector<Boat>& boats) {
    for (int i = 0; i < BOAT_COUNT; ++i) {
        boats[i].boatNumber = i + 1;
        boats[i].moneyTakenToday = 0.0;
        boats[i].hoursHiredToday = 0;
        boats[i].returnTime = OPEN_TIME;
    }
}

void hireBoat(Boat& boat) {
    int hireTime;
    char hireDuration;
    cout << "Hiring boat number " << boat.boatNumber << ".\n";
    cout << "Enter the hire time (hour in 24-hour format): ";
    cin >> hireTime;

    if (hireTime < OPEN_TIME || hireTime >= CLOSE_TIME) {
        cout << "Error: No boat can be hired before 10:00 or returned after 17:00.\n";
        return;
    }

    cout << "Hire duration (f for full hour, h for half hour): ";
    cin >> hireDuration;
    if (hireDuration == 'f') {
        boat.moneyTakenToday += FULL_HOUR_RATE;
        boat.hoursHiredToday += 1;
        boat.returnTime = hireTime + 1;
    } else if (hireDuration == 'h') {
        boat.moneyTakenToday += HALF_HOUR_RATE;
        boat.hoursHiredToday += 1;
        boat.returnTime = hireTime + 1; // Assume half hour still blocks the full hour
    } else {
        cout << "Error: Invalid hire duration entered.\n";
    }
}

bool isAvailable(const Boat& boat, int currentTime) {
    return currentTime >= boat.returnTime;
}

void findNextAvailableBoat(const vector<Boat>& boats, int currentTime) {
    vector<int> availableBoats;
    int earliestAvailableTime = CLOSE_TIME;

    for (const Boat& boat : boats) {
        if (isAvailable(boat, currentTime)) {
            availableBoats.push_back(boat.boatNumber);
        } else {
            earliestAvailableTime = min(earliestAvailableTime, boat.returnTime);
        }
    }

    if (!availableBoats.empty()) {
        cout << "Available boats: ";
        for (int boatNumber : availableBoats) {
            cout << boatNumber << " ";
        }
        cout << endl;
    } else {
        cout << "No boats available. Earliest available time: " << earliestAvailableTime << ":00\n";
    }
}

void endOfDayReport(const vector<Boat>& boats) {
    double totalMoneyTaken = 0.0;
    int totalHoursHired = 0;
    int boatsNotUsed = 0;
    int mostUsedBoatNumber = 0;
    int mostHoursHired = 0;

    for (const Boat& boat : boats) {
        totalMoneyTaken += boat.moneyTakenToday;
        totalHoursHired += boat.hoursHiredToday;
        if (boat.hoursHiredToday == 0) {
            boatsNotUsed++;
        }
        if (boat.hoursHiredToday > mostHoursHired) {
            mostHoursHired = boat.hoursHiredToday;
            mostUsedBoatNumber = boat.boatNumber;
        }
    }

    cout << "End of day report:\n";
    cout << "Total money taken: $" << fixed << setprecision(2) << totalMoneyTaken << endl;
    cout << "Total hours boats were hired: " << totalHoursHired << endl;
    cout << "Number of boats not used: " << boatsNotUsed << endl;
    cout << "Boat number used the most: " << mostUsedBoatNumber << endl;
}
