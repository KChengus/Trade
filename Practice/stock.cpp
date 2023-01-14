#include <cstdlib>
#include <iostream>
#include <string>
#include <deque>
#include "settings.cpp"
#include <time.h>
#ifndef STOCK
#define STOCK

struct MarketDirection {
    // TODO a better a algorithm for generating random nums
    MarketDirection() {
        setTrend();
    };
    // Long Term and Short Term
    bool isLTUpTr;
    int lsMaxChange = 200; // 100 = 1% 
    bool isSTUpTr;
    int stMaxChange = 300;

    int news[2] = {1, 0}; // news[direction, scale], scale = 0-100, 0 is no impact on market, 100 huge impact  
    // TODO implement scale to be normal distributed
    
    void setTrend() {
        isLTUpTr = time(NULL) % 2; 
        isSTUpTr = time(NULL) % 2;
    }
    void reverseLTUp() { isLTUpTr = !isLTUpTr; }
    void reverseSTUp() { isSTUpTr= !isSTUpTr; }

    double getTrendPerc(bool isUp) {
        int lsChange = genRandInt(0, lsMaxChange);
        int stChange = genRandInt(0, stMaxChange);
        if (isUp) {
            return (isLTUpTr ? lsChange : 0) + (isSTUpTr ? stChange : 0);
        }
        return (isLTUpTr ? 0 : -lsChange) + (isSTUpTr ? 0 : -stChange);
    }

    std::string getCurMarketDir() {
        std::string s = "";
        if (isLTUpTr) {
            s += "Long Term Uptrend";
        } else {
            s += "Long Term Downtrend";
        }
        s += "\t\t\t";
        if (isSTUpTr) {
            s += "Short Term Uptrend";
        } else {
            s += "Short Term Downtrend";
        }
        return s;
    }
};

struct RandEvents {
    unsigned int ltChProb = 100; // 1 / ltChProb of changing direc
    unsigned int stChProb = 10;
    // Optimise this cleaner
    bool changeLT() {
        return !genRandInt(0, ltChProb);
    };
    bool changeST() {
        return !genRandInt(0, stChProb);
    };
};

/*
Stock created, focus on:
* Market Direction
    - Is Long term uptrend
    - Is Short term uptrend
    - News
* Current Volatility
* Liquitity (optional)
*/

class Stock {
    // Encapsulation
    public:
        // Constructor
        Stock(std::string name, double currentPrice=0, double mVol=100) : 
            name(name), currentPrice(currentPrice), maxVolatility(mVol) {}
        
        // class memebers
        std::string getName() { return name; };
        double getCurrentPrice() { return currentPrice; }
        double getCurrentVolatility() { return curVolatility; }
        // forward decleration
        void updatePrice(); 
        void update_events();
        void update_market_direction();


    protected:
        std::string name;
        double currentPrice;
        double maxVolatility; // highest procentage change in promile
        double curVolatility;
        MarketDirection mD;
        RandEvents randEv;
        std::deque<double> price100days;
        unsigned int demand;
        unsigned int supply;
        unsigned int news; // value 0-100;

};


void Stock::updatePrice() {

    int lowerBound  = -maxVolatility + mD.getTrendPerc(0);

    int higherBound =  maxVolatility + mD.getTrendPerc(1);
    curVolatility = generateRandVola(lowerBound, higherBound);
    double price = currentPrice + currentPrice*curVolatility;
    if (price100days.size() >= 100) {
        price100days.pop_front();
    }
    //price100days.push_back(currentPrice);
    currentPrice = price;
} 

void Stock::update_events() {
    if (randEv.changeLT()) {
        mD.reverseLTUp();
    }
    if (randEv.changeST()) {
        mD.reverseSTUp();
    }
}

void Stock::update_market_direction() {
    //std::cout << "Current MarkD:\t\t" << mD.getCurMarketDir()  << '\n';
}

#endif 
