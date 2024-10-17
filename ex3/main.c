#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{
    int pos_x = 0;
    int pos_y = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("Error SDL2 Init : %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) 
    {
        printf("Erreur d'initialisation de la SDL_Image\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Exercice 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 160, SDL_WINDOW_OPENGL);

    if (window == NULL) 
    {
        printf("Error while creating a window : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Erreur à la création du renderer\n");
        return 1;
    }

    SDL_Surface* surface = IMG_Load("ball.png");
    if (surface == NULL) 
    {
        printf("Error loading image %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) 
    {
        printf("Error creating texture\n");
        return 1;
    }

    SDL_FreeSurface(surface);   

    while(1)
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                break;
            }
            else if (e.type == SDL_KEYDOWN) 
            {
                if (e.key.keysym.scancode == SDL_SCANCODE_W) {

                    pos_y -= 8;
                    SDL_Rect rect = {pos_x, pos_y, 16, 16};
                    SDL_Rect rect_img = {0, 0, 16, 16};
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                    SDL_RenderPresent(renderer);
            
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_S) {
                    pos_y += 8;
                    SDL_Rect rect = {pos_x, pos_y, 16, 16};
                    SDL_Rect rect_img = {32, 0, 16, 16};
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                    SDL_RenderPresent(renderer);
            
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_A) {
                    pos_x -= 8;
                    SDL_Rect rect = {pos_x, pos_y, 16, 16};
                    SDL_Rect rect_img = {48, 0, 16, 16};
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                    SDL_RenderPresent(renderer);
            
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_D) {
                    pos_x += 8;
                    SDL_Rect rect = {pos_x, pos_y, 16, 16};
                    SDL_Rect rect_img = {16, 0, 16, 16};
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                    SDL_RenderPresent(renderer);
            
                }
            }
        }
    }


    SDL_Quit();
    return 0; 
}