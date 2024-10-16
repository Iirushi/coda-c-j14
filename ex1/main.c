#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 160, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialisation de SDL_image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur d'initialisation de SDL_Image: %s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur de création du renderer: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Utilisez un chemin relatif
    SDL_Surface* surface = IMG_Load("bottle.png");
    if (!surface) {
        printf("Erreur de chargement de l'image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Libérer la surface après la création de la texture
    if (!texture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Calcul des coordonnées pour centrer l'image
    SDL_Rect destRect = { (160 - 16) / 2, (160 - 16) / 2, 16, 16 };

    // Boucle d'événements
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}