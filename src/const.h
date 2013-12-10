#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

using std::string;

// -- GAME --//
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int FPS = 100;
const int LIVE_SCOPE = 2000;

// -- ELODIE -- //
const int DAMAGE_CD = 25;

// -- LEVEL -- //
const float ZOOM_LEVEL = 2;

// Immersion Bar
const float IMMERSION_BAR_X = 540;
const float IMMERSION_BAR_Y = 50;
const float IMMERSION_BAR_W = 200;
const float IMMERSION_BAR_H = 15;

const float IMMERSION_BAR_OUTLINE_THICKNESS = 2;

const sf::Color IMMERSION_BAR_FILL = sf::Color(0x73, 0xC8, 0xA9, 0xFF);
const sf::Color IMMERSION_BAR_OUTLINE = sf::Color(0x31, 0x55, 0x48, 0xFF);

// -- MAPS --
// ASCII Map
// Terrain
static const char MAP_GROUND = '#';

// Characters
static const char MAP_ELODIE = 'E';

// Enemies
static const char MAP_SHEEP = 'S';
static const char MAP_MAGMACUBE = 'M';

// Misc
static const char MAP_LINE_BREAK = '\n';
static const char MAP_NULL = ' ';
static const char MAP_NULL2 = '.';

// -- PATHS -- //
// Tiles
const string TILES_TEXTURES_PATH = "assets/img/sprites/tiles/extended";

const string LEVELENV_FIELD = "field";
const string LEVELENV_UNIL = "unil";
const string LEVELENV_CASTLE = "castle";
const string LEVELENV_VOLCANO = "volcano";
const string LEVELENV_FRELJORD = "freljord";

const string TILETYPE_GROUND = "ground";
const string TILETYPE_ROCK = "rock";
const string TILETYPE_ICE = "ice";

// Entities
const string ENTITIES_JSON_PATH = "assets/img/sprites";

const string ENTITYNAME_ELODIE = "elodie";
const string ENTITYNAME_SHEEP = "sheep";
const string ENTITYNAME_MAGMACUBE = "magmacube";

const string ENTITYTYPE_ELODIE = "";
const string ENTITYTYPE_ENEMY = "enemies";

// Sounds
const string SOUNDS_PATH = "assets/sounds";

const string SOUND_TYPE_PUNCH = "punch";
const int SOUND_TYPE_PUNCH_MAX = 2;

const string SOUND_TYPE_FOOTSTEP_GRASS = "footstep_grass";
const int SOUND_TYPE_FOOTSTEP_GRASS_MAX = 3;

// const string SOUND_TYPE_FOOTSTEP_GROUND = "footstep/ground";
// const string SOUND_TYPE_FOOTSTEP_ROCK = "footstep/rock";

const string MUSIC_PATH = "assets/music";
const string OVERWORLD_MUSIC = "overworld.ogg";
const string LEVEL_MUSIC = "level.ogg";

#endif // CONST_H_INCLUDED
