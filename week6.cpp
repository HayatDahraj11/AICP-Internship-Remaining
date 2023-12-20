#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const double GRAVEL_SAND_MIN_WEIGHT = 49.9;
const double GRAVEL_SAND_MAX_WEIGHT = 50.1;
const double CEMENT_MIN_WEIGHT = 24.9;
const double CEMENT_MAX_WEIGHT = 25.1;
const double PRICE_CEMENT = 3.0;
const double PRICE_GRAVEL = 2.0;
const double PRICE_SAND = 2.0;
const double SPECIAL_PACK_PRICE = 10.0;

bool checkSack(char content, double weight) {
    switch (content) {
        case 'C':
            return weight > CEMENT_MIN_WEIGHT && weight < CEMENT_MAX_WEIGHT;
        case 'G':
        case 'S':
            return weight > GRAVEL_SAND_MIN_WEIGHT && weight < GRAVEL_SAND_MAX_WEIGHT;
        default:
            return false;
    }
}

double calculateRegularPrice(int cementSacks, int gravelSacks, int sandSacks) {
    return cementSacks * PRICE_CEMENT + gravelSacks * PRICE_GRAVEL + sandSacks * PRICE_SAND;
}

void calculateDiscountPrice(int &cementSacks, int &gravelSacks, int &sandSacks, double &totalPrice, double &amountSaved) {
    int specialPacks = min({cementSacks, gravelSacks / 2, sandSacks / 2});
    cementSacks -= specialPacks;
    gravelSacks -= specialPacks * 2;
    sandSacks -= specialPacks * 2;
    
    double regularPrice = calculateRegularPrice(cementSacks, gravelSacks, sandSacks);
    double discountPrice = specialPacks * SPECIAL_PACK_PRICE;
    amountSaved = (specialPacks * (PRICE_CEMENT + 2 * (PRICE_GRAVEL + PRICE_SAND))) - discountPrice;
    totalPrice = regularPrice + discountPrice;
}

int main() {
    char content;
    double weight;
    int cementSacks = 0, gravelSacks = 0, sandSacks = 0, rejectedSacks = 0;
    double totalWeight = 0.0, totalPrice, amountSaved;

    cout << fixed << setprecision(2);

    // Task 1 - Check the contents and weight of a single sack
    cout << "Enter the contents (C, G, S) and weight of the sack: ";
    cin >> content >> weight;
    if (!checkSack(content, weight)) {
        cout << "This sack has been rejected due to ";
        if (content != 'C' && content != 'G' && content != 'S') {
            cout << "incorrect content.";
        } else {
            cout << "incorrect weight.";
        }
        cout << endl;
        return 1;
    }
    cout << "Accepted: " << content << " with weight " << weight << "kg\n";

    // Task 2 - Check a customer’s order for delivery
    cout << "Enter the number of sacks of cement, gravel, and sand required for the order: ";
    cin >> cementSacks >> gravelSacks >> sandSacks;

    for (int i = 0; i < cementSacks; i++) {
        if (!checkSack('C', CEMENT_MAX_WEIGHT)) {
            rejectedSacks++;
        } else {
            totalWeight += CEMENT_MAX_WEIGHT;
        }
    }
    for (int i = 0; i < gravelSacks; i++) {
        if (!checkSack('G', GRAVEL_SAND_MAX_WEIGHT)) {
            rejectedSacks++;
        } else {
            totalWeight += GRAVEL_SAND_MAX_WEIGHT;
        }
    }
    for (int i = 0; i < sandSacks; i++) {
        if (!checkSack('S', GRAVEL_SAND_MAX_WEIGHT)) {
            rejectedSacks++;
        } else {
            totalWeight += GRAVEL_SAND_MAX_WEIGHT;
        }
    }

    cout << "Total weight of the order: " << totalWeight << "kg\n";
    cout << "Number of sacks rejected from the order: " << rejectedSacks << endl;

    // Task 3 - Calculate the price for a customer’s order
    calculateDiscountPrice(cementSacks, gravelSacks, sandSacks, totalPrice, amountSaved);
    cout << "Regular price for the order: $" << calculateRegularPrice(cementSacks, gravelSacks, sandSacks) << endl;
    cout << "Discounted price for the order: $" << totalPrice << endl;
    cout << "Amount saved: $" << amountSaved << endl;

    return 0;
}
