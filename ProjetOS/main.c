#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define TASKBAR_HEIGHT 50

// Fonction pour dessiner du texte
void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Notification en haut
void afficherNotification(SDL_Renderer* renderer, TTF_Font* font, const char* message, int width) {
    SDL_Color notifColor = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, message, notifColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect notifRect = {20, 20, surface->w + 20, surface->h + 20};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // fond
    SDL_RenderFillRect(renderer, &notifRect);

    SDL_Rect textRect = {notifRect.x + 10, notifRect.y + 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_Delay(3000);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("<OS_NAME>", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          960, 540, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("Sansation-Regular.ttf", 20);
    if (!font) {
        printf("Erreur de police : %s\n", TTF_GetError());
        return 1;
    }

    // Boot screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    drawText(renderer, font, "<OS_NAME> Démmarrage...", 350, 250, (SDL_Color){0, 200, 255});
    SDL_RenderPresent(renderer);
    SDL_Delay(2500);

    bool running = true;
    SDL_Event event;
    bool menuOpen = false;

    afficherNotification(renderer, font,
        "Exemple de notification : vous pouvez reprendre ce système pour votre OS", 960);

    while (running) {
        int winW, winH;
        SDL_GetWindowSize(window, &winW, &winH);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;
                // Clique sur le bouton menu
                if (mx >= 10 && mx <= 100 && my >= winH - TASKBAR_HEIGHT + 10 && my <= winH - 10) {
                    menuOpen = !menuOpen;
                }
            }
        }

        // Dessin du bureau
        SDL_SetRenderDrawColor(renderer, 40, 40, 60, 255);
        SDL_RenderClear(renderer);

        // Dessin de la taskbar
        SDL_Rect taskbar = {0, winH - TASKBAR_HEIGHT, winW, TASKBAR_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderFillRect(renderer, &taskbar);

        // Bouton "Menu"
        SDL_Rect menuBtn = {10, winH - TASKBAR_HEIGHT + 10, 90, 30};
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderFillRect(renderer, &menuBtn);
        drawText(renderer, font, "Menu", 25, winH - TASKBAR_HEIGHT + 15, (SDL_Color){255, 255, 255});

        // Si menu ouvert
        if (menuOpen) {
            SDL_Rect menu = {10, winH - TASKBAR_HEIGHT - 110, 200, 100};
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(renderer, &menu);
            drawText(renderer, font, "- Paramètres", 20, winH - TASKBAR_HEIGHT - 95, (SDL_Color){255, 255, 255});
            drawText(renderer, font, "- Terminal", 20, winH - TASKBAR_HEIGHT - 65, (SDL_Color){255, 255, 255});
            drawText(renderer, font, "- Quitter", 20, winH - TASKBAR_HEIGHT - 35, (SDL_Color){255, 255, 255});
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Nettoyage
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
