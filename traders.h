#include <string>
#include "stock.cpp"
#include <vector>

#ifndef TRADERS
#define TRADERS

// Parent Class
class Trader {
    public:
        Trader(std::string name, long equity, unsigned int ticks) : name(name), equity(equity), ticks(ticks) {};
        std::vector<Stock> positions; 
        // pullout should be implemented differently based on the type of trader


    protected:
        unsigned long equity;
        std::string name;

        unsigned int ticks;
};  

// Inheritance of parent class into child classes
class SwingTrader : public Trader {
    public:
        SwingTrader(long equity) : Trader("Swing", equity, 1) {};
        // void update_change(double prob) {
        //     open_pos_prob = prob;
        // }

    private:
        // double open_pos_prob = 0.20;
};

class DayTrader : public Trader{

};

class FundamentalTrader : public Trader{

}; 


#endif