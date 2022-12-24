#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

#define EMPTY_CELL '_'
#define FILLED_CELL '1'

SDL_Color convert(const glm::vec3& color);

// Player

extern glm::vec2 PLAYER_POS;
extern float PLAYER_ANGLE;
extern float PLAYER_SPEED;
extern float PLAYER_ROT_SPEED;

// Raycasting
extern float FOV;
extern float HALF_FOV;
extern int NUM_RAYS;
extern int HALF_NUM_RAYS;
extern float DELTA_ANGLE;
extern int MAX_DEPTH;

// Game

extern float TAU;

extern const char *TITLE;
extern int WIDTH;
extern int HEIGHT;
extern float FPS;

// Color

extern const glm::vec3 kCOLOR_MAROON;
extern const glm::vec3 kCOLOR_DARK_RED;
extern const glm::vec3 kCOLOR_BROWN;
extern const glm::vec3 kCOLOR_FIREBRICK;
extern const glm::vec3 kCOLOR_CRIMSON;
extern const glm::vec3 kCOLOR_RED;
extern const glm::vec3 kCOLOR_TOMATO;
extern const glm::vec3 kCOLOR_CORAL;
extern const glm::vec3 kCOLOR_INDIAN_RED;
extern const glm::vec3 kCOLOR_LIGHT_CORAL;
extern const glm::vec3 kCOLOR_DARK_SALMON;
extern const glm::vec3 kCOLOR_SALMON;
extern const glm::vec3 kCOLOR_LIGHT_SALMON;
extern const glm::vec3 kCOLOR_ORANGE_RED;
extern const glm::vec3 kCOLOR_DARK_ORANGE;
extern const glm::vec3 kCOLOR_ORANGE;
extern const glm::vec3 kCOLOR_GOLD;
extern const glm::vec3 kCOLOR_DARK_GOLDEN_ROD;
extern const glm::vec3 kCOLOR_GOLDEN_ROD;
extern const glm::vec3 kCOLOR_PALE_GOLDEN_ROD;
extern const glm::vec3 kCOLOR_DARK_KHAKI;
extern const glm::vec3 kCOLOR_KHAKI;
extern const glm::vec3 kCOLOR_OLIVE;
extern const glm::vec3 kCOLOR_YELLOW;
extern const glm::vec3 kCOLOR_YELLOW_GREEN;
extern const glm::vec3 kCOLOR_DARK_OLIVE_GREEN;
extern const glm::vec3 kCOLOR_OLIVE_DRAB;
extern const glm::vec3 kCOLOR_LAWN_GREEN;
extern const glm::vec3 kCOLOR_CHARTREUSE;
extern const glm::vec3 kCOLOR_GREEN_YELLOW;
extern const glm::vec3 kCOLOR_DARK_GREEN;
extern const glm::vec3 kCOLOR_GREEN;
extern const glm::vec3 kCOLOR_FOREST_GREEN;
extern const glm::vec3 kCOLOR_LIME;
extern const glm::vec3 kCOLOR_LIME_GREEN;
extern const glm::vec3 kCOLOR_LIGHT_GREEN;
extern const glm::vec3 kCOLOR_PALE_GREEN;
extern const glm::vec3 kCOLOR_DARK_SEA_GREEN;
extern const glm::vec3 kCOLOR_MEDIUM_SPRING_GREEN;
extern const glm::vec3 kCOLOR_SPRING_GREEN;
extern const glm::vec3 kCOLOR_SEA_GREEN;
extern const glm::vec3 kCOLOR_MEDIUM_AQUA_MARINE;
extern const glm::vec3 kCOLOR_MEDIUM_SEA_GREEN;
extern const glm::vec3 kCOLOR_LIGHT_SEA_GREEN;
extern const glm::vec3 kCOLOR_DARK_SLATE_GRAY;
extern const glm::vec3 kCOLOR_TEAL;
extern const glm::vec3 kCOLOR_DARK_CYAN;
extern const glm::vec3 kCOLOR_AQUA;
extern const glm::vec3 kCOLOR_CYAN;
extern const glm::vec3 kCOLOR_LIGHT_CYAN;
extern const glm::vec3 kCOLOR_DARK_TURQUOISE;
extern const glm::vec3 kCOLOR_TURQUOISE;
extern const glm::vec3 kCOLOR_MEDIUM_TURQUOISE;
extern const glm::vec3 kCOLOR_PALE_TURQUOISE;
extern const glm::vec3 kCOLOR_AQUA_MARINE;
extern const glm::vec3 kCOLOR_POWDER_BLUE;
extern const glm::vec3 kCOLOR_CADET_BLUE;
extern const glm::vec3 kCOLOR_STEEL_BLUE;
extern const glm::vec3 kCOLOR_CORN_FLOWER_BLUE;
extern const glm::vec3 kCOLOR_DEEP_SKY_BLUE;
extern const glm::vec3 kCOLOR_DODGER_BLUE;
extern const glm::vec3 kCOLOR_LIGHT_BLUE;
extern const glm::vec3 kCOLOR_SKY_BLUE;
extern const glm::vec3 kCOLOR_LIGHT_SKY_BLUE;
extern const glm::vec3 kCOLOR_MIDNIGHT_BLUE;
extern const glm::vec3 kCOLOR_NAVY;
extern const glm::vec3 kCOLOR_DARK_BLUE;
extern const glm::vec3 kCOLOR_MEDIUM_BLUE;
extern const glm::vec3 kCOLOR_BLUE;
extern const glm::vec3 kCOLOR_ROYAL_BLUE;
extern const glm::vec3 kCOLOR_BLUE_VIOLET;
extern const glm::vec3 kCOLOR_INDIGO;
extern const glm::vec3 kCOLOR_DARK_SLATE_BLUE;
extern const glm::vec3 kCOLOR_SLATE_BLUE;
extern const glm::vec3 kCOLOR_MEDIUM_SLATE_BLUE;
extern const glm::vec3 kCOLOR_MEDIUM_PURPLE;
extern const glm::vec3 kCOLOR_DARK_MAGENTA;
extern const glm::vec3 kCOLOR_DARK_VIOLET;
extern const glm::vec3 kCOLOR_DARK_ORCHID;
extern const glm::vec3 kCOLOR_MEDIUM_ORCHID;
extern const glm::vec3 kCOLOR_PURPLE;
extern const glm::vec3 kCOLOR_THISTLE;
extern const glm::vec3 kCOLOR_PLUM;
extern const glm::vec3 kCOLOR_VIOLET;
extern const glm::vec3 kCOLOR_MAGENTA;
extern const glm::vec3 kCOLOR_ORCHID;
extern const glm::vec3 kCOLOR_MEDIUM_VIOLET_RED;
extern const glm::vec3 kCOLOR_PALE_VIOLET_RED;
extern const glm::vec3 kCOLOR_DEEP_PINK;
extern const glm::vec3 kCOLOR_HOT_PINK;
extern const glm::vec3 kCOLOR_LIGHT_PINK;
extern const glm::vec3 kCOLOR_PINK;
extern const glm::vec3 kCOLOR_ANTIQUE_WHITE;
extern const glm::vec3 kCOLOR_BEIGE;
extern const glm::vec3 kCOLOR_BISQUE;
extern const glm::vec3 kCOLOR_BLANCHED_ALMOND;
extern const glm::vec3 kCOLOR_WHEAT;
extern const glm::vec3 kCOLOR_CORN_SILK;
extern const glm::vec3 kCOLOR_LEMON_CHIFFON;
extern const glm::vec3 kCOLOR_LIGHT_GOLDEN_ROD_YELLOW;
extern const glm::vec3 kCOLOR_LIGHT_YELLOW;
extern const glm::vec3 kCOLOR_SADDLE_BROWN;
extern const glm::vec3 kCOLOR_SIENNA;
extern const glm::vec3 kCOLOR_CHOCOLATE;
extern const glm::vec3 kCOLOR_PERU;
extern const glm::vec3 kCOLOR_SANDY_BROWN;
extern const glm::vec3 kCOLOR_BURLY_WOOD;
extern const glm::vec3 kCOLOR_TAN;
extern const glm::vec3 kCOLOR_ROSY_BROWN;
extern const glm::vec3 kCOLOR_MOCCASIN;
extern const glm::vec3 kCOLOR_NAVAJO_WHITE;
extern const glm::vec3 kCOLOR_PEACH_PUFF;
extern const glm::vec3 kCOLOR_MISTY_ROSE;
extern const glm::vec3 kCOLOR_LAVENDER_BLUSH;
extern const glm::vec3 kCOLOR_LINEN;
extern const glm::vec3 kCOLOR_OLD_LACE;
extern const glm::vec3 kCOLOR_PAPAYA_WHIP;
extern const glm::vec3 kCOLOR_SEA_SHELL;
extern const glm::vec3 kCOLOR_MINT_CREAM;
extern const glm::vec3 kCOLOR_SLATE_GRAY;
extern const glm::vec3 kCOLOR_LIGHT_SLATE_GRAY;
extern const glm::vec3 kCOLOR_LIGHT_STEEL_BLUE;
extern const glm::vec3 kCOLOR_LAVENDER;
extern const glm::vec3 kCOLOR_FLORAL_WHITE;
extern const glm::vec3 kCOLOR_ALICE_BLUE;
extern const glm::vec3 kCOLOR_GHOST_WHITE;
extern const glm::vec3 kCOLOR_HONEYDEW;
extern const glm::vec3 kCOLOR_IVORY;
extern const glm::vec3 kCOLOR_AZURE;
extern const glm::vec3 kCOLOR_SNOW;
extern const glm::vec3 kCOLOR_BLACK;
extern const glm::vec3 kCOLOR_DIM_GRAY;
extern const glm::vec3 kCOLOR_GRAY;
extern const glm::vec3 kCOLOR_DARK_GRAY;
extern const glm::vec3 kCOLOR_SILVER;
extern const glm::vec3 kCOLOR_LIGHT_GRAY;
extern const glm::vec3 kCOLOR_GAINSBORO;
extern const glm::vec3 kCOLOR_WHITE_SMOKE;
extern const glm::vec3 kCOLOR_WHITE;