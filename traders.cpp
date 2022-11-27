#include <string>
#include "stock.cpp"
#include <vector>

#ifndef TRADERS
#define TRADERS

// Parent Class
class Trader {
    public:
        Trader(std::string name, long equity, int tpslPerc, unsigned int ticks) : name(name), equity(equity), tpslPerc(tpslPerc), ticks(ticks) {};
        std::vector<Stock> positions; 
        void setTPSL(int perc, int initialPrice) {
            double frac = perc * 1.0 / 100;
            TPSL = {(1+frac)*initialPrice, (1-frac)*initialPrice};
        }
        // pullout should be implemented differently based on the type of trader
    protected:
        unsigned long equity;
        int tpslPerc;
        std::vector<double> TPSL;
        
        std::string name;
        unsigned int ticks;
};  

// Inheritance of parent class into child classes
class SwingTrader : public Trader {
    void friend exit_trades(Trader);
    public:
        SwingTrader(long equity) : Trader("Swing", equity, 1, 1) {};
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

void exit_trades(Trader trader) {
    // Trader can be any of the other trade classes
    // this is an example of polymorphism
    for (Stock stock : trader.positions) {

    }
}

#endif