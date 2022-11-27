#include <iostream>
#include "traders.cpp"
#include "settings.cpp"

void run() {
    SwingTrader swing(1000);
    Stock eur("Euro", 100,100);
    swing.positions.push_back(eur);
    unsigned int microsec = 100000;

    // TODO implement clock system
    // options : 10hz, 20hz, 100hz

    Stock* currentStock;
    while (true) {
        currentStock = &swing.positions[0];
        currentStock->updatePrice();
        currentStock->update_events();
        currentStock->update_market_direction();
        std::cout << "Current Price:\t\t" << currentStock->getCurrentPrice() << '\n'; 
        std::cout << "Current Volat:\t\t" << currentStock->getCurrentVolatility()  << "\n\n\n\n\n\n\n\n";
        usleep(microsec);
    }
    return;
}

int main() {
    run();
}
