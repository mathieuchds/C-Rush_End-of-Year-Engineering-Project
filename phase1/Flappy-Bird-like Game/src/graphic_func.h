#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture** tab_texture);

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );

void play_with_texture_2(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer, float zoom);

void scroll_background(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer, int scroll_x, float zoom);

void pipe_spawn(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * pipe_up, SDL_Texture * pipe_down, int tab_pipe[8], int it_pipe);

void bee_moove(SDL_Window * window, SDL_Renderer * renderer, int bee, SDL_Texture * texture, float zoom, int sensi);

