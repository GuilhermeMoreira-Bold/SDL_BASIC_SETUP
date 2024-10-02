#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL2/SDL_image.h>
#include <SDL.h>


void inicializarSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("Erro ao incializar o SDL: %s\n", SDL_GetError());
	}
}

SDL_Window* criarJanela(){
	//cria Janela
	SDL_Window* window = SDL_CreateWindow("Exibir Imagem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800, 600, 0);
	
	if(!window){
		printf("Erro ao criar a janela: %s\n", SDL_GetError());
		SDL_Quit();
	}
	return window;
}

SDL_Renderer* criarRenderizador(SDL_Window* window){
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,0);
	if(!renderer){
		printf("Erro ao criar renderizador: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
	}	
}

SDL_Surface* carregarImagem(){
	SDL_Surface* surface = IMG_Load("images.jpeg");
	if(!surface){
		printf("Erro ao criar a superficie %s\n", SDL_GetError());
	}
}

SDL_Texture* carregarTextura(SDL_Renderer* renderer,SDL_Surface* surface,SDL_Window* window){
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture){
		printf("Erro ao criar textura: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}

void renderizar(SDL_Texture* texture,SDL_Renderer* renderer){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	while(1){
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT){
			break;		
		}	
	}
}

void desligarPrograma(SDL_Texture* texture,SDL_Renderer* renderer,SDL_Window* window){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
int main(){
	inicializarSDL();
	SDL_Window* window = criarJanela();
	SDL_Renderer* renderer = criarRenderizador(window);
	SDL_Texture* texture = carregarTextura(renderer,carregarImagem(),window);
	renderizar(texture,renderer);
	desligarPrograma(texture,renderer,window);
	
	return 0;
}
