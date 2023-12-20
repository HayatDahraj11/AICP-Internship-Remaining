#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function prototypes
void initializeDonationSystem(vector<string>& charities, vector<double>& totals);
int getCharityChoice(const vector<string>& charities);
double getShoppingBill();
double calculateDonation(double shoppingBill);
void recordDonation(int charityChoice, double donation, vector<double>& totals);
void showTotals(const vector<string>& charities, const vector<double>& totals);
void displayGrandTotal(const vector<double>& totals);

int main() {
    vector<string> charities(3);
    vector<double> totals(3, 0.0);

    // TASK 1 - Set up the donation system
    initializeDonationSystem(charities, totals);

    char proceed = 'y';
    do {
        // TASK 2 - Record and total each donation
        int charityChoice = getCharityChoice(charities);
        if (charityChoice == -1) {
            // TASK 3 - Show the totals so far
            showTotals(charities, totals);
            displayGrandTotal(totals);
            break;
        }

        double shoppingBill = getShoppingBill();
        double donation = calculateDonation(shoppingBill);
        recordDonation(charityChoice, donation, totals);

        cout << "Donated $" << fixed << setprecision(2) << donation << " to " << charities[charityChoice - 1] << ".\n";

        cout << "Enter another donation? (y/n): ";
        cin >> proceed;
    } while (proceed == 'y');

    return 0;
}

void initializeDonationSystem(vector<string>& charities, vector<double>& totals) {
    cout << "Enter the names of three charities:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Charity " << (i + 1) << ": ";
        getline(cin, charities[i]);
    }
    fill(totals.begin(), totals.end(), 0.0);
}

int getCharityChoice(const vector<string>& charities) {
    int choice;
    do {
        cout << "Choose a charity to donate to (enter -1 to show totals):\n";
        for (int i = 0; i < charities.size(); ++i) {
            cout << (i + 1) << ". " << charities[i] << "\n";
        }
        cin >> choice;
        if (choice == -1) break;
    } while (choice < 1 || choice > 3);
    return choice;
}

double getShoppingBill() {
    double shoppingBill;
    cout << "Enter the value of the customer's shopping bill: $";
    cin >> shoppingBill;
    return shoppingBill;
}

double calculateDonation(double shoppingBill) {
    return shoppingBill * 0.01; // 1% of the bill
}

void recordDonation(int charityChoice, double donation, vector<double>& totals) {
    totals[charityChoice - 1] += donation;
}

void showTotals(const vector<string>& charities, const vector<double>& totals) {
    vector<pair<string, double>> charityTotals;
    for (size_t i = 0; i < charities.size(); ++i) {
        charityTotals.emplace_back(charities[i], totals[i]);
    }
    sort(charityTotals.begin(), charityTotals.end(),
        [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second > b.second;
        });

    cout << "Totals donated to each charity:\n";
    for (const auto& charityTotal : charityTotals) {
        cout << charityTotal.first << ": $" << fixed << setprecision(2) << charityTotal.second << "\n";
    }
}

void displayGrandTotal(const vector<double>& totals) {
    double grandTotal = 0.0;
    for (const double& total : totals) {
        grandTotal += total;
    }
    cout << "GRAND TOTAL DONATED TO CHARITY: $" << fixed << setprecision(2) << grandTotal << "\n";
}
