#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

using std::string;

// -- GAME --//
const int DEFAULT_MUTE = false; // TODO Change me to false
const int FULLSCREEN = false; // TODO Change me to true
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int FPS = 60;
const int LIVE_SCOPE = 2000;
const float MAX_TIME_FRAME = 1.0/10.0;

// -- ELODIE -- //
const int DAMAGE_CD = 25;
const int ELODIE_JUMP = -450;
const int ELODIE_SPEED = 250;
const float INC_PV_TIMER = 0.2;
const float ATTACK_COOLDOWN = 0.5;

// -- ENEMY -- //
const int SHEEP_DAMAGE = 10;
const int GHOST_DAMAGE = 12;
const int GHOST_STEP = 5;
const int GHOST_LIMIT_Y = 150;
const int GHOST_SPEED_X = 100;
const int MAGMACUBE_DAMAGE = 25;
const int MAGMACUBE_JUMP_CD = 50;
const int MAGMACUBE_MOVE_X = 200;
const int MAGMACUBE_MOVE_Y = 400;
const int BRISTLE_DAMAGE = 60;
const int BRISTLE_SPEED_X = 500;
const int BRISTLE_SPEED_Y = 200;
const int BRISTLE_DETECTION = 450;
const int SPIKES_DAMAGE = 50;
const int PORO_SPEED_X = 255;
const int PORO_SPEED_Y = 300;
const int PORO_DETECTION = 350;

// -- LEVEL -- //
const float ZOOM_LEVEL = 2;
const int BLOCK_SIZE = 32;
const int CAMERA_TOL = 50;
const bool GOD_MODE = false; // TODO set to false
const int HORIZONTAL_DISPLAY_MARGIN = WINDOW_WIDTH/(2*ZOOM_LEVEL) + 2*BLOCK_SIZE;
const int VERTICAL_DISPLAY_MARGIN = WINDOW_HEIGHT/(2*ZOOM_LEVEL) + 2*BLOCK_SIZE;
const int NUMLEVELS = 8;

// Immersion Bar
const float IMMERSION_BAR_X = 540;
const float IMMERSION_BAR_DELTA_X = 2;
const float IMMERSION_BAR_Y = 50;
const float IMMERSION_BAR_DELTA_Y = 1;
const float IMMERSION_BAR_W = 204;
const float IMMERSION_BAR_H = 19;
const float IMMERSION_BG_W = 202;
const float IMMERSION_BG_H = 18;
const float IMMERSION_IMAGE_W = 406;
const float IMMERSION_IMAGE_H = 38;

const float IMMERSION_BAR_OUTLINE_THICKNESS = 2;

const sf::Color IMMERSION_BAR_FILL = sf::Color(0x73, 0xC8, 0xA9, 0xFF);
const sf::Color IMMERSION_BAR_OUTLINE = sf::Color(0x31, 0x55, 0x48, 0xFF);

// -- SCORE -- //
const float SCORE_OVERWORLD_SPRITE_SIZE = 40;
const float SCORE_LEVEL_SPRITE_SIZE = 20;

// -- MAPS --
// ASCII Map
// Terrain
static const char MAP_GROUND = '#';
static const char MAP_ICE = 'I';
static const char MAP_DIRT = 'D';

// Characters
static const char MAP_ELODIE = 'E';

// Enemies
static const char MAP_SHEEP = 'S';
static const char MAP_MAGMACUBE = 'M';
static const char MAP_GHOST = 'G';
static const char MAP_BRISTLE = 'B';
static const char MAP_SPIKES = 'P';
static const char MAP_PORO = 'O';
static const char MAP_BONUS = 'N';

// Misc
static const char MAP_PORTAL = 'F';
static const char MAP_LINE_BREAK = '\n';
static const char MAP_NULL = ' ';
static const char MAP_NULL2 = '.';

// -- PATHS -- //
// Global path
const string GLOBALFONT_PATH = "assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf";

// Tiles
const string TILES_TEXTURES_PATH = "assets/img/sprites/tiles/extended";
const string ENVIRONMENT_TEXTURES_PATH = "assets/img/sprites/environments";

const string LEVELENV_FIELD = "field";
const string LEVELENV_UNIL = "unil";
const string LEVELENV_CASTLE = "castle";
const string LEVELENV_VOLCANO = "volcano";
const string LEVELENV_FRELJORD = "freljord";

const string TILETYPE_GROUND = "ground";
const string TILETYPE_DIRT = "dirt";
const string TILETYPE_ROCK = "rock";
const string TILETYPE_ICE = "ice";

// Entities
const string ENTITIES_JSON_PATH = "assets/img/sprites";

const string ENTITYNAME_ELODIE = "elodie";
const string ENTITYNAME_SHEEP = "sheep";
const string ENTITYNAME_GHOST = "ghost";
const string ENTITYNAME_MAGMACUBE = "magmacube";
const string ENTITYNAME_BRISTLE = "bristle";
const string ENTITYNAME_SPIKES = "spikes";
const string ENTITYNAME_PORTAL = "portal";
const string ENTITYNAME_PORO = "poro";
const string ENTITYNAME_SPRITE = "sprite";

const string ENTITYTYPE_ELODIE = "";
const string ENTITYTYPE_ENEMY = "enemies";
const string ENTITYTYPE_MISC = "misc";
const string ENTITYTYPE_BONUS = "bonus";
// Sounds
const string SOUNDS_PATH = "assets/sounds";

const string SOUND_TYPE_PUNCH = "punch";
const int SOUND_TYPE_PUNCH_MAX = 2;

const string SOUND_TYPE_WOOSH = "woosh";
const int SOUND_TYPE_WOOSH_MAX = 1;

const string SOUND_TYPE_SPIKES = "spikes";
const int SOUND_TYPE_SPIKES_MAX = 2;

const string SOUND_TYPE_SHEEP = "sheep";
const int SOUND_TYPE_SHEEP_MAX = 4;

const string SOUND_TYPE_MAGMACUBE = "magmacube";
const int SOUND_TYPE_MAGMACUBE_MAX = 3;

const string SOUND_TYPE_FOOTSTEP_GROUND = "footstep_ground";
const int SOUND_TYPE_FOOTSTEP_GROUND_MAX = 4;

const string SOUND_TYPE_FOOTSTEP_GRASS = "footstep_grass";
const int SOUND_TYPE_FOOTSTEP_GRASS_MAX = 3;

const string SOUND_TYPE_BRISTLE = "bristle";
const int SOUND_TYPE_BRISTLE_MAX = 2;

const string SOUND_TYPE_BOTTLE = "bottle";
const int SOUND_TYPE_BOTTLE_MAX = 1;

const int PUNCH_VOLUME = 55;
const int WOOSH_VOLUME = 50;

// const string SOUND_TYPE_FOOTSTEP_ROCK = "footstep_rock";
const string MUSIC_PATH = "assets/music";
const string OVERWORLD_MUSIC = "overworld.ogg";
const string LEVEL_MUSIC = "level.ogg";
const string DEATH_MUSIC = "death.ogg";
const string END_MUSIC = "end.ogg";

//Menu
const string MENU_SELECTOR_PATH = "assets/img/sprites/poro.png";
const string MENU_BACKGROUND_PATH = "assets/img/sprites/menu/background.png";
const string MENU_ANIMATED_BACKGROUND_PATH = "assets/img/sprites/title/poro";
const string MENU_TITLE_TEXT = "assets/img/sprites/title/title.png";

const string MENU_NEWGAME_LABEL = "New game";
const string MENU_STATS_LABEL = "Stats";
const string MENU_RESUME_LABEL = "Resume";
const string MENU_LEAVELEVEL_LABEL = "Leave level";
const string MENU_QUITGAME_LABEL = "Quit game";
const string MENU_TITLEMENU_LABEL = "Title menu";
const string MENU_SAVEGAME_LABEL = "Save game";
const string MENU_LOADGAME_LABEL = "Load game";
const string MENU_SLOT_PREFIX_LABEL = "Slot ";

const int MENU_TITLE_TEXT_LEFT = 150;
const int MENU_TITLE_TEXT_TOP = 20;
const float MENU_X = 200;
const float MENU_Y = 220;
const float MENU_WIDTH = 300;
const sf::Color MENU_ITEM_COLOR = sf::Color(0xEE, 0xAA, 0x4A, 0xFF);
const sf::Color MENU_BACKGROUND_OUTLINE_COLOR = sf::Color(0x29, 0x43, 0x07, 0xFF);
const int MENU_ITEMS_INTERSPACE = 50;
const int MENU_CHAR_SIZE = 30;
const int MENU_BACKGROUND_FIRST_FRAME = 69;
const int MENU_BACKGROUND_LAST_FRAME = 100;
const int MENU_LOADING_X = 1100;
const int MENU_LOADING_Y = 660;

//Game over
const float GAMEOVER_INTERSPACE = 50;

//Console
const int CONSOLE_NLINES = 6;

// Scores board
const float SCORES_INTERSPACE = 100;
const int SCORES_CHAR_SIZE = 25;
const float SCORES_STARTY = 100;
const int BONUS_POINTS = 50;
const int BONUS_NODAMAGES = 1000;

// Stats board
const float STATS_MARGIN = 50;
const float STATS_WIDTH_CATEGORY = 100;
const int STATS_CHAR_SIZE = 15;

// Saves
const int NUMSLOTS = 3;

#endif // CONST_H_INCLUDED
