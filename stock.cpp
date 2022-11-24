#include <string>
#include <deque>
#include "settings.cpp"
#include <time.h>
#ifndef STOCK
#define STOCK

struct MarketDirection {
    // TODO a better a algorithm for generating random nums
    MarketDirection() {
        setLTUpTr();
        setSTUpTr();

    };
    // Long Term and Short Term
    bool isLTUpTr;
    bool isSTUpTr;

    int news[2] = {1, 0}; // news[direction, scale], scale = 0-100, 0 is no impact on market, 100 huge impact  
    // TODO implement scale to be normal distributed
    
    void setLTUpTr() {
        isLTUpTr = time(NULL) % 2; 
    }
    void setSTUpTr() {
        isSTUpTr = time(NULL) % 2;
    }
};

class Stock {
    // Encapsulation
    public:
        // Constructor
        Stock(std::string name, double currentPrice=0, double mVol=10) : 
            name(name), maxVolatility(mVol) {updatePrice(currentPrice); }
        
        // class memebers
        std::string getName() { return name; };
        double getCurrentPrice() { return currentPrice; }
        // forward declerations
        void priceChange(double);
        void updatePrice(double); 
        void generateRandomVolatility();

    protected:
        std::string name;
        double currentPrice;
        double maxVolatility; // highest procentage change in promile
        double curVolatility;
        MarketDirection mD;
        std::deque<double> price100days;
        unsigned int demand;
        unsigned int supply;
        unsigned int news; // value 0-100;

};

void Stock::generateRandomVolatility() {
    curVolatility = generateRandomNum(maxVolatility);
}
void Stock::updatePrice(double price) {
    if (price100days.size() <= 100) {
        price100days.pop_front();
    }
    price100days.push_back(price);
    currentPrice = price;
} 
void Stock::priceChange(double volitility) {
    updatePrice(currentPrice + currentPrice*volitility); 
}
#endif 
