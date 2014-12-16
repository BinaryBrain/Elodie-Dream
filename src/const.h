#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

using std::string;

// -- GAME --//
const int DEFAULT_MUTE = false;
const int FULLSCREEN = false;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int FPS = 60;
const int LIVE_SCOPE = 2000;
const float MAX_TIME_FRAME = 1.0/10.0;
const double GAME_VERSION = 1.1;
const bool DEV_MODE = false;

// -- LEVEL -- //
const int BLOCK_SIZE = 32;
const int CAMERA_TOL = 50;
const bool GOD_MODE = false;
// -- MAPS --
// ASCII Map
// Terrain
static const char MAP_GROUND = '#';
static const char MAP_ICE = 'I';
static const char MAP_DIRT = 'D';
static const char MAP_BOX = 'T';
static const char MAP_METAL = 'o';
static const char MAP_ASTEROID = 'X';

// Characters
static const char MAP_ELODIE = 'E';

// Enemies
static const char MAP_SHEEP = 'S';
static const char MAP_MAGMACUBE = 'M';
static const char MAP_GHOST = 'G';
static const char MAP_BRISTLE = 'B';
static const char MAP_METEORITE = 'W';
static const char MAP_ALIEN = 'A';
static const char MAP_LASER = 'L';
static const char MAP_SPIKES = 'P';
static const char MAP_RAVEN = 'v';
static const char MAP_PORO = 'O';
static const char MAP_BONUS = 'N';

// Misc
static const char MAP_PORTAL = 'F';
static const char MAP_ROCKET = 'R';
static const char MAP_LINE_BREAK = '\n';
static const char MAP_NULL = ' ';
static const char MAP_NULL2 = '.';

// -- PATHS -- //
// Global path
const string GLOBALFONT_PATH = "assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf";
const string LANGUAGES_PATH = "assets/config/languages";
const string SETTINGS_PATH = "settings";

// Tiles
const string TILES_TEXTURES_PATH = "assets/img/sprites/tiles/extended";
const string ENVIRONMENT_TEXTURES_PATH = "assets/img/sprites/environments";

const string LEVELENV_FIELD = "field";
const string LEVELENV_UNIL = "unil";
const string LEVELENV_CASTLE = "castle";
const string LEVELENV_VOLCANO = "volcano";
const string LEVELENV_FRELJORD = "freljord";
const string LEVELENV_SPACE = "space";
const string LEVELENV_MODERN = "modern";

const string TILETYPE_GROUND = "ground";
const string TILETYPE_DIRT = "dirt";
const string TILETYPE_ROCK = "rock";
const string TILETYPE_ICE = "ice";
const string TILETYPE_BOX = "box";
const string TILETYPE_METAL = "metal";
const string TILETYPE_ASTEROID = "asteroid";

// Entities
const string ENTITIES_JSON_PATH = "assets/img/sprites";

const string ENTITYNAME_ELODIE = "elodie";
const string ENTITYNAME_ROCKET = "rocket";
const string ENTITYNAME_SHEEP = "sheep";
const string ENTITYNAME_GHOST = "ghost";
const string ENTITYNAME_MAGMACUBE = "magmacube";
const string ENTITYNAME_BRISTLE = "bristle";
const string ENTITYNAME_METEORITE = "meteorite";
const string ENTITYNAME_ALIEN = "alien";
const string ENTITYNAME_LASER = "laser";
const string ENTITYNAME_SPIKES = "spikes";
const string ENTITYNAME_RAVEN = "raven";
const string ENTITYNAME_PORTAL = "portal";
const string ENTITYNAME_PORO = "poro";
const string ENTITYNAME_SPRITE = "sprite";

const string ENTITYTYPE_ELODIE = "";
const string ENTITYTYPE_ENEMY = "enemies";
const string ENTITYTYPE_MISC = "misc";
const string ENTITYTYPE_BONUS = "bonus";
// Sounds
const string SOUNDS_PATH = "assets/sounds";

const string SOUND_TYPE_OUTCH = "outch";
const int SOUND_TYPE_OUTCH_MAX = 2;

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

const string SOUND_TYPE_RAVEN = "raven";
const int SOUND_TYPE_RAVEN_MAX = 2;

const string SOUND_TYPE_FOOTSTEP_GROUND = "footstep_ground";
const int SOUND_TYPE_FOOTSTEP_GROUND_MAX = 4;

const string SOUND_TYPE_FOOTSTEP_GRASS = "footstep_grass";
const int SOUND_TYPE_FOOTSTEP_GRASS_MAX = 3;

const string SOUND_TYPE_BRISTLE = "bristle";
const int SOUND_TYPE_BRISTLE_MAX = 2;

const string SOUND_TYPE_METEORITE = "meteorite";
const int SOUND_TYPE_METEORITE_MAX = 3;

const string SOUND_TYPE_ALIEN = "alien";
const int SOUND_TYPE_ALIEN_MAX = 1;

const string SOUND_TYPE_LASER = "laser";
const int SOUND_TYPE_LASER_MAX = 1;

const string SOUND_TYPE_BOTTLE = "bottle";
const int SOUND_TYPE_BOTTLE_MAX = 1;

const int PUNCH_VOLUME = 55;
const int WOOSH_VOLUME = 50;

// const string SOUND_TYPE_FOOTSTEP_ROCK = "footstep_rock";
const string MUSIC_PATH = "assets/music";
const string OVERWORLD_MUSIC = "overworld.ogg";
const string LEVEL_MUSIC = "level.ogg";
const string END_MUSIC = "end.ogg";

// Menu
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

#endif // CONST_H_INCLUDED
