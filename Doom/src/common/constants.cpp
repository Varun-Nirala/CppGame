#include "common/constants.h"

SDL_Color convert(const glm::vec3& color)
{
	SDL_Color c;
	c.r = (Uint8)(color.r * 255);
	c.g = (Uint8)(color.g * 255);
	c.b = (Uint8)(color.b * 255);
	c.a = 255;

	return c;
}

// Player

extern glm::vec2 PLAYER_POS				= { 1.5f, 5.0f };
extern float PLAYER_ANGLE				= 0.0f;
extern float PLAYER_SPEED				= 0.004f;
extern float PLAYER_ROT_SPEED			= 0.002f;

// Raycasting

float FOV								= (float)M_PI / 3.0f;
float HALF_FOV							= FOV / 2.0f;
int NUM_RAYS							= WIDTH / 2;
int HALF_NUM_RAYS						= NUM_RAYS / 2;
float DELTA_ANGLE						= FOV / NUM_RAYS;
int MAX_DEPTH							= 20;

// Game

extern float TAU						= 2.0f * (float)M_PI;

const char* TITLE						= "Doom";
int WIDTH								= 1600;
int HEIGHT								= 900;
int HALF_WIDTH							= WIDTH / 2;
int HALF_HEIGHT							= HEIGHT / 2;
float FPS								= 60.0f;

float SCREEN_DIST						= HALF_WIDTH / glm::tan(HALF_FOV);
int SCALE								= WIDTH / NUM_RAYS;


// Texture

int TEXTURE_SIZE						= 256;
int HALF_TEXTURE_SIZE					= TEXTURE_SIZE / 2;

// Color

const glm::vec3 kCOLOR_MAROON                               { 0.50, 0.00, 0.00 };
const glm::vec3 kCOLOR_DARK_RED                             { 0.55, 0.00, 0.00 };
const glm::vec3 kCOLOR_BROWN                                { 0.65, 0.16, 0.16 };
const glm::vec3 kCOLOR_FIREBRICK                            { 0.70, 0.13, 0.13 };
const glm::vec3 kCOLOR_CRIMSON                              { 0.86, 0.08, 0.24 };
const glm::vec3 kCOLOR_RED                                  { 1.00, 0.00, 0.00 };
const glm::vec3 kCOLOR_TOMATO                               { 1.00, 0.39, 0.28 };
const glm::vec3 kCOLOR_CORAL                                { 1.00, 0.50, 0.31 };
const glm::vec3 kCOLOR_INDIAN_RED                           { 0.80, 0.36, 0.36 };
const glm::vec3 kCOLOR_LIGHT_CORAL                          { 0.80, 0.50, 0.50 };
const glm::vec3 kCOLOR_DARK_SALMON                          { 0.91, 0.59, 0.48 };
const glm::vec3 kCOLOR_SALMON                               { 0.98, 0.50, 0.45 };
const glm::vec3 kCOLOR_LIGHT_SALMON                         { 1.00, 0.63, 0.48 };
const glm::vec3 kCOLOR_ORANGE_RED                           { 1.00, 0.27, 0.00 };
const glm::vec3 kCOLOR_DARK_ORANGE                          { 1.00, 0.55, 0.00 };
const glm::vec3 kCOLOR_ORANGE                               { 1.00, 0.65, 0.00 };
const glm::vec3 kCOLOR_GOLD                                 { 1.00, 0.84, 0.00 };
const glm::vec3 kCOLOR_DARK_GOLDEN_ROD                      { 0.72, 0.53, 0.04 };
const glm::vec3 kCOLOR_GOLDEN_ROD                           { 0.85, 0.65, 0.13 };
const glm::vec3 kCOLOR_PALE_GOLDEN_ROD                      { 0.93, 0.91, 0.67 };
const glm::vec3 kCOLOR_DARK_KHAKI                           { 0.74, 0.72, 0.42 };
const glm::vec3 kCOLOR_KHAKI                                { 0.94, 0.90, 0.55 };
const glm::vec3 kCOLOR_OLIVE                                { 0.50, 0.50, 0.00 };
const glm::vec3 kCOLOR_YELLOW                               { 1.00, 1.00, 0.00 };
const glm::vec3 kCOLOR_YELLOW_GREEN                         { 0.60, 0.80, 0.20 };
const glm::vec3 kCOLOR_DARK_OLIVE_GREEN                     { 0.33, 0.42, 0.18 };
const glm::vec3 kCOLOR_OLIVE_DRAB                           { 0.42, 0.56, 0.14 };
const glm::vec3 kCOLOR_LAWN_GREEN                           { 0.49, 0.99, 0.00 };
const glm::vec3 kCOLOR_CHARTREUSE                           { 0.50, 1.00, 0.00 };
const glm::vec3 kCOLOR_GREEN_YELLOW                         { 0.68, 1.00, 0.18 };
const glm::vec3 kCOLOR_DARK_GREEN                           { 0.00, 0.39, 0.00 };
const glm::vec3 kCOLOR_GREEN                                { 0.00, 0.50, 0.00 };
const glm::vec3 kCOLOR_FOREST_GREEN                         { 0.13, 0.55, 0.13 };
const glm::vec3 kCOLOR_LIME                                 { 0.00, 1.00, 0.00 };
const glm::vec3 kCOLOR_LIME_GREEN                           { 0.20, 0.80, 0.20 };
const glm::vec3 kCOLOR_LIGHT_GREEN                          { 0.56, 0.93, 0.56 };
const glm::vec3 kCOLOR_PALE_GREEN                           { 0.60, 0.98, 0.60 };
const glm::vec3 kCOLOR_DARK_SEA_GREEN                       { 0.56, 0.74, 0.56 };
const glm::vec3 kCOLOR_MEDIUM_SPRING_GREEN                  { 0.00, 0.98, 0.60 };
const glm::vec3 kCOLOR_SPRING_GREEN                         { 0.00, 1.00, 0.50 };
const glm::vec3 kCOLOR_SEA_GREEN                            { 0.18, 0.55, 0.34 };
const glm::vec3 kCOLOR_MEDIUM_AQUA_MARINE                   { 0.40, 0.80, 0.67 };
const glm::vec3 kCOLOR_MEDIUM_SEA_GREEN                     { 0.24, 0.70, 0.44 };
const glm::vec3 kCOLOR_LIGHT_SEA_GREEN                      { 0.13, 0.70, 0.67 };
const glm::vec3 kCOLOR_DARK_SLATE_GRAY                      { 0.18, 0.31, 0.31 };
const glm::vec3 kCOLOR_TEAL                                 { 0.00, 0.50, 0.50 };
const glm::vec3 kCOLOR_DARK_CYAN                            { 0.00, 0.55, 0.55 };
const glm::vec3 kCOLOR_AQUA                                 { 0.00, 1.00, 1.00 };
const glm::vec3 kCOLOR_CYAN                                 { 0.00, 1.00, 1.00 };
const glm::vec3 kCOLOR_LIGHT_CYAN                           { 0.88, 1.00, 1.00 };
const glm::vec3 kCOLOR_DARK_TURQUOISE                       { 0.00, 0.81, 0.82 };
const glm::vec3 kCOLOR_TURQUOISE                            { 0.25, 0.88, 0.82 };
const glm::vec3 kCOLOR_MEDIUM_TURQUOISE                     { 0.28, 0.82, 0.80 };
const glm::vec3 kCOLOR_PALE_TURQUOISE                       { 0.69, 0.93, 0.93 };
const glm::vec3 kCOLOR_AQUA_MARINE                          { 0.50, 1.00, 0.83 };
const glm::vec3 kCOLOR_POWDER_BLUE                          { 0.69, 0.88, 0.90 };
const glm::vec3 kCOLOR_CADET_BLUE                           { 0.37, 0.62, 0.63 };
const glm::vec3 kCOLOR_STEEL_BLUE                           { 0.27, 0.51, 0.71 };
const glm::vec3 kCOLOR_CORN_FLOWER_BLUE                     { 0.39, 0.58, 0.93 };
const glm::vec3 kCOLOR_DEEP_SKY_BLUE                        { 0.00, 0.75, 1.00 };
const glm::vec3 kCOLOR_DODGER_BLUE                          { 0.12, 0.56, 1.00 };
const glm::vec3 kCOLOR_LIGHT_BLUE                           { 0.68, 0.85, 0.90 };
const glm::vec3 kCOLOR_SKY_BLUE                             { 0.53, 0.81, 0.92 };
const glm::vec3 kCOLOR_LIGHT_SKY_BLUE                       { 0.53, 0.81, 0.98 };
const glm::vec3 kCOLOR_MIDNIGHT_BLUE                        { 0.99, 0.20, 0.05 };
const glm::vec3 kCOLOR_NAVY                                 { 0.00, 0.00, 0.50 };
const glm::vec3 kCOLOR_DARK_BLUE                            { 0.00, 0.00, 0.55 };
const glm::vec3 kCOLOR_MEDIUM_BLUE                          { 0.00, 0.00, 0.80 };
const glm::vec3 kCOLOR_BLUE                                 { 0.00, 0.00, 1.00 };
const glm::vec3 kCOLOR_ROYAL_BLUE                           { 0.25, 0.41, 0.88 };
const glm::vec3 kCOLOR_BLUE_VIOLET                          { 0.54, 0.17, 0.89 };
const glm::vec3 kCOLOR_INDIGO                               { 0.29, 0.00, 0.51 };
const glm::vec3 kCOLOR_DARK_SLATE_BLUE                      { 0.28, 0.24, 0.55 };
const glm::vec3 kCOLOR_SLATE_BLUE                           { 0.42, 0.35, 0.80 };
const glm::vec3 kCOLOR_MEDIUM_SLATE_BLUE                    { 0.48, 0.41, 0.93 };
const glm::vec3 kCOLOR_MEDIUM_PURPLE                        { 0.58, 0.44, 0.86 };
const glm::vec3 kCOLOR_DARK_MAGENTA                         { 0.55, 0.00, 0.55 };
const glm::vec3 kCOLOR_DARK_VIOLET                          { 0.58, 0.00, 0.83 };
const glm::vec3 kCOLOR_DARK_ORCHID                          { 0.60, 0.20, 0.80 };
const glm::vec3 kCOLOR_MEDIUM_ORCHID                        { 0.73, 0.33, 0.83 };
const glm::vec3 kCOLOR_PURPLE                               { 0.50, 0.00, 0.50 };
const glm::vec3 kCOLOR_THISTLE                              { 0.85, 0.75, 0.85 };
const glm::vec3 kCOLOR_PLUM                                 { 0.87, 0.63, 0.87 };
const glm::vec3 kCOLOR_VIOLET                               { 0.93, 0.51, 0.93 };
const glm::vec3 kCOLOR_MAGENTA                              { 1.00, 0.00, 1.00 };
const glm::vec3 kCOLOR_ORCHID                               { 0.85, 0.44, 0.84 };
const glm::vec3 kCOLOR_MEDIUM_VIOLET_RED                    { 0.78, 0.08, 0.52 };
const glm::vec3 kCOLOR_PALE_VIOLET_RED                      { 0.86, 0.44, 0.58 };
const glm::vec3 kCOLOR_DEEP_PINK                            { 1.00, 0.08, 0.58 };
const glm::vec3 kCOLOR_HOT_PINK                             { 1.00, 0.41, 0.71 };
const glm::vec3 kCOLOR_LIGHT_PINK                           { 1.00, 0.71, 0.76 };
const glm::vec3 kCOLOR_PINK                                 { 1.00, 0.75, 0.80 };
const glm::vec3 kCOLOR_ANTIQUE_WHITE                        { 0.98, 0.92, 0.84 };
const glm::vec3 kCOLOR_BEIGE                                { 0.96, 0.96, 0.86 };
const glm::vec3 kCOLOR_BISQUE                               { 1.00, 0.89, 0.77 };
const glm::vec3 kCOLOR_BLANCHED_ALMOND                      { 1.00, 0.92, 0.80 };
const glm::vec3 kCOLOR_WHEAT                                { 0.96, 0.87, 0.70 };
const glm::vec3 kCOLOR_CORN_SILK                            { 1.00, 0.97, 0.86 };
const glm::vec3 kCOLOR_LEMON_CHIFFON                        { 1.00, 0.98, 0.80 };
const glm::vec3 kCOLOR_LIGHT_GOLDEN_ROD_YELLOW              { 0.98, 0.98, 0.82 };
const glm::vec3 kCOLOR_LIGHT_YELLOW                         { 1.00, 1.00, 0.88 };
const glm::vec3 kCOLOR_SADDLE_BROWN                         { 0.55, 0.27, 0.07 };
const glm::vec3 kCOLOR_SIENNA                               { 0.63, 0.32, 0.18 };
const glm::vec3 kCOLOR_CHOCOLATE                            { 0.82, 0.41, 0.12 };
const glm::vec3 kCOLOR_PERU                                 { 0.80, 0.52, 0.25 };
const glm::vec3 kCOLOR_SANDY_BROWN                          { 0.96, 0.64, 0.38 };
const glm::vec3 kCOLOR_BURLY_WOOD                           { 0.87, 0.72, 0.53 };
const glm::vec3 kCOLOR_TAN                                  { 0.82, 0.71, 0.55 };
const glm::vec3 kCOLOR_ROSY_BROWN                           { 0.74, 0.56, 0.56 };
const glm::vec3 kCOLOR_MOCCASIN                             { 1.00, 0.89, 0.71 };
const glm::vec3 kCOLOR_NAVAJO_WHITE                         { 1.00, 0.87, 0.68 };
const glm::vec3 kCOLOR_PEACH_PUFF                           { 1.00, 0.85, 0.73 };
const glm::vec3 kCOLOR_MISTY_ROSE                           { 1.00, 0.89, 0.88 };
const glm::vec3 kCOLOR_LAVENDER_BLUSH                       { 1.00, 0.94, 0.96 };
const glm::vec3 kCOLOR_LINEN                                { 0.98, 0.94, 0.90 };
const glm::vec3 kCOLOR_OLD_LACE                             { 0.99, 0.96, 0.90 };
const glm::vec3 kCOLOR_PAPAYA_WHIP                          { 1.00, 0.94, 0.84 };
const glm::vec3 kCOLOR_SEA_SHELL                            { 1.00, 0.96, 0.93 };
const glm::vec3 kCOLOR_MINT_CREAM                           { 0.96, 1.00, 0.98 };
const glm::vec3 kCOLOR_SLATE_GRAY                           { 0.44, 0.50, 0.56 };
const glm::vec3 kCOLOR_LIGHT_SLATE_GRAY                     { 0.47, 0.53, 0.60 };
const glm::vec3 kCOLOR_LIGHT_STEEL_BLUE                     { 0.69, 0.77, 0.87 };
const glm::vec3 kCOLOR_LAVENDER                             { 0.90, 0.90, 0.98 };
const glm::vec3 kCOLOR_FLORAL_WHITE                         { 1.00, 0.98, 0.94 };
const glm::vec3 kCOLOR_ALICE_BLUE                           { 0.94, 0.97, 1.00 };
const glm::vec3 kCOLOR_GHOST_WHITE                          { 0.97, 0.97, 1.00 };
const glm::vec3 kCOLOR_HONEYDEW                             { 0.94, 1.00, 0.94 };
const glm::vec3 kCOLOR_IVORY                                { 1.00, 1.00, 0.94 };
const glm::vec3 kCOLOR_AZURE                                { 0.94, 1.00, 1.00 };
const glm::vec3 kCOLOR_SNOW                                 { 1.00, 0.98, 0.98 };
const glm::vec3 kCOLOR_BLACK                                { 0.00, 0.00, 0.00 };
const glm::vec3 kCOLOR_DIM_GRAY                             { 0.41, 0.41, 0.41 };
const glm::vec3 kCOLOR_GRAY                                 { 0.50, 0.50, 0.50 };
const glm::vec3 kCOLOR_DARK_GRAY                            { 0.66, 0.66, 0.66 };
const glm::vec3 kCOLOR_SILVER                               { 0.75, 0.75, 0.75 };
const glm::vec3 kCOLOR_LIGHT_GRAY                           { 0.83, 0.83, 0.83 };
const glm::vec3 kCOLOR_GAINSBORO                            { 0.86, 0.86, 0.86 };
const glm::vec3 kCOLOR_WHITE_SMOKE							{ 0.95, 0.95, 0.95 };
const glm::vec3 kCOLOR_WHITE								{ 1.00, 1.00, 1.00 };