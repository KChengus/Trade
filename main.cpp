#include <SDL.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Practice/traders.cpp"
#include "Practice/settings.cpp"

// Glob constants
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT= 900;

const int DOTS_WIDTH = 5;
const int DOTS_HEIGHT = 5;
const int DOTS_BUFFER = WINDOW_WIDTH / 10;

const int EQUITY = 500;
const int SLEEP = 100000;

// Graph

std::vector<double> dots(WINDOW_WIDTH-DOTS_BUFFER, WINDOW_HEIGHT / 2); // SDL lib

// Stock and Trader
SwingTrader swing(EQUITY);
Stock eur("EURO", 100, 100);


// The window we'll be rendering to
SDL_Window* window = nullptr;

// Renderer
SDL_Renderer* renderer = nullptr;



// Forward declaration
bool init();
void dots_event(int);

int main(int argc, char* argv[]) {

    // if Window or image can't be loaded then terminate program
    if (!init()) {
        printf("Failed to initialize!\n");
        return EXIT_FAILURE;
    }
    srand((unsigned) time(nullptr));
    SDL_Rect rect;
    rect.w = DOTS_WIDTH;
    rect.h = DOTS_HEIGHT;

    SDL_Event e; bool quit=false;
    int pDots = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit=true;

        // draw background
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // dots event
        dots_event(pDots);
        ++pDots;
        if (pDots >= dots.size()) pDots = 0;
        // draw dots
        int pCur;
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < dots.size(); ++i) {
            pCur = (pDots + i) % dots.size();
            rect.x = i;
            rect.y = dots[pCur];
            SDL_RenderFillRect(renderer, &rect);
        }
        // Show what we have drawn
        SDL_RenderPresent(renderer);
        }
    }
}

bool init() {
    // Initialize SDL
    if (SDL_Init( SDL_INIT_VIDEO ) < 0){
        printf(" SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    // Create window
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) < 0)
    {
        printf(" SDL Window or Renderer could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    return true;
}

void dots_event(int pDots) {
    eur.updatePrice();
    eur.update_events();
    eur.update_market_direction();
    dots[pDots] = eur.getCurrentPrice();

}