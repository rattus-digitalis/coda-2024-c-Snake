#include "snake.h"

void initSnake(Snake *snake) {
    snake->length = 5;
    snake->dx = TILE_SIZE;
    snake->dy = 0;
    for (int i = 0; i < snake->length; i++) {
        snake->position[i].x = WINDOW_WIDTH / 2 - i * TILE_SIZE;
        snake->position[i].y = WINDOW_HEIGHT / 2;
    }
}

void drawSnake(SDL_Renderer *renderer, Snake *snake, SDL_Texture *nyancattexture) {
    for (int i = 0; i < snake->length; i++) {
        SDL_Rect dest_rect = {snake->position[i].x, snake->position[i].y, 32, 32};

        if (i == 0) {
            // Determine head direction based on dx and dy
            SDL_Rect rect_img_head;

            if (snake->dx > 0) {
                // Moving right
                rect_img_head = (SDL_Rect){32, 0, 32, 32};  // Head facing right
            } else if (snake->dx < 0) {
                // Moving left
                rect_img_head = (SDL_Rect){64, 0, 32, 32};  // Head facing left
            } else if (snake->dy > 0) {
                // Moving down
                rect_img_head = (SDL_Rect){128, 0, 32, 32};  // Head facing down
            } else if (snake->dy < 0) {
                // Moving up
                rect_img_head = (SDL_Rect){96, 0, 32, 32};  // Head facing up
            }

            // Render the head with the correct direction
            SDL_RenderCopy(renderer, nyancattexture, &rect_img_head, &dest_rect);
        }
        else if (i == snake->length - 1) {
            // Tail of the snake
            SDL_Rect rect_img_tail = {96, 0, 32, 32};  // Image section for the tail
            SDL_RenderCopy(renderer, nyancattexture, &rect_img_tail, &dest_rect);
        }
        else {
            // Body logic (as before)
            Point prev = snake->position[i - 1];    // Previous segment
            Point next = snake->position[i + 1];    // Next segment

            if (prev.x == snake->position[i].x && next.x == snake->position[i].x)
                 {
                // Straight body part
                SDL_Rect rect_img_body = {192, 0, 32, 32};  // Image section for the body
                SDL_RenderCopy(renderer, nyancattexture, &rect_img_body, &dest_rect);
            }
            else if (prev.y == snake->position[i].y && next.y == snake->position[i].y)
              {
                  SDL_Rect rect_img_body = {160, 0, 32, 32};
                  SDL_RenderCopy(renderer, nyancattexture, &rect_img_body, &dest_rect);
              }
            else {
                // Corner logic (as explained previously)
                SDL_Rect rect_img_corner;
                if ((prev.x > snake->position[i].x && next.y > snake->position[i].y) ||
                    (next.x > snake->position[i].x && prev.y > snake->position[i].y)) {
                    rect_img_corner = (SDL_Rect){288, 0, 32, 32};  // Bottom-right corner
                } else if ((prev.x > snake->position[i].x && next.y < snake->position[i].y) ||
                           (next.x > snake->position[i].x && prev.y < snake->position[i].y)) {
                    rect_img_corner = (SDL_Rect){224, 0, 32, 32};  // Top-right corner
                } else if ((prev.x < snake->position[i].x && next.y > snake->position[i].y) ||
                           (next.x < snake->position[i].x && prev.y > snake->position[i].y)) {
                    rect_img_corner = (SDL_Rect){320, 0, 32, 32};  // Bottom-left corner
                } else if ((prev.x < snake->position[i].x && next.y < snake->position[i].y) ||
                           (next.x < snake->position[i].x && prev.y < snake->position[i].y)) {
                    rect_img_corner = (SDL_Rect){256, 0, 32, 32};  // Top-left corner
                }
                SDL_RenderCopy(renderer, nyancattexture, &rect_img_corner, &dest_rect);
            }
        }
    }
}

void updateSnake(Snake *snake) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->position[i] = snake->position[i - 1];
    }
    snake->position[0].x += snake->dx;
    snake->position[0].y += snake->dy;
}

void growSnake(Snake *snake) {
    snake->length++;
}

