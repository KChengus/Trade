#include <iostream>
#include "traders.h"
#include "settings.cpp"

void run() {
    SwingTrader swing(1000);
    Stock eur("Euro", 10, 20);
    swing.positions.push_back(eur);
    unsigned int microsec = 100000;
    double change;

    // TODO implement clock system
    // options : 10hz, 20hz, 100hz

    while (true) {
        Stock currentStock = swing.positions[0];
        currentStock.priceChange(change);
        std::cout << "Current Price:\t\t\t\t\t\t\t" << currentStock.getCurrentPrice() << "\n\n\n\n\n\n\n\n\n\n\n";
        usleep(microsec);
    }
    return;
}

int main() {
    run();
}
