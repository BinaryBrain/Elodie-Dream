#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include <string>
#include <map>

using std::string;

// -- GAME --//
const int FPS = 100;

// -- LEVEL -- //
const float ZOOM_LEVEL = 3;

// -- PATHS -- //
// Tiles
const string TILES_TEXTURES_PATH = "assets/img/sprites/tiles/extended";

const string LEVELENV_FIELD = "field";
const string LEVELENV_UNIL = "unil";
const string LEVELENV_CASTLE = "castle";
const string LEVELENV_VOLCANO = "volcano";
const string LEVELENV_FREJLORD = "frejlord";

const string TILETYPE_GROUND = "ground";
const string TILETYPE_ROCK = "rock";
const string TILETYPE_ICE = "ice";

// Enemies
const string ENTITIES_JSON_PATH = "assets/img/sprites";

const string ENTITYNAME_ELODIE = "elodie";
const string ENTITYNAME_SHEEP = "sheep";

const string ENTITYTYPE_ELODIE = "";
const string ENTITYTYPE_ENEMY = "enemies";

// Sounds
const string SOUNDS_PATH = "assets/sounds";

const string SOUND_TYPE_PUNCH = "punch";

#endif // CONST_H_INCLUDED
