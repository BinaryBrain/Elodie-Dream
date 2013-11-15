// ASCII Map
// Terrain
var MAP_GROUND = '#';

// Characters
var MAP_ELODIE = 'E';

// Misc
var MAP_LINE_BREAK = '\n';
var MAP_NULL = ' ';

// Images
images = []
images[MAP_GROUND] = "../../assets/img/sprites/tilesets/autotiles/ground1extended.png"
images[MAP_ELODIE] = "../../assets/img/sprites/tilesets/autotiles/ground1extended.png"

function parse(level, tiles, entities) {
  var y = 0
  var x = 0

  for(var i = 0; i < level.length; i++) {
    if(y >= tiles.length) {
      tiles.push([])
    }

    switch(level[i]) {
      case MAP_GROUND:
        tiles[y].push(new Tile(images[MAP_GROUND], 0, 0))
        break

      case MAP_LINE_BREAK:
        y++;
        x=0;
        break

      case MAP_NULL:
        tiles[y].push(undefined)
        break
      
      default:
        tiles[y].push(undefined)
        break
    }
    
    ++x;
  }
}

var TileSide = {  TOP: 0x01,
                  BOTTOM: 0X02,
                  LEFT: 0X04,
                  RIGHT: 0X08,
                  TOP_LEFT: 0X10,
                  TOP_RIGHT: 0X20,
                  BOTTOM_LEFT: 0X40,
                  BOTTOM_RIGHT: 0X80,
                }

// Once the Map is parsed, we can automaticaly choose the right tiles
function beautify(tiles) {
  for(var y = 0; y < tiles.length; y++) {
    for(var x = 0; x < tiles[y].length; x++) {
      if(tiles[y][x] !== undefined) {
        if(y >= 1 && !tiles[y-1][x]) {
            tiles[y][x].addSide(TileSide.TOP)
        }

        if(x >= 1 && !tiles[y][x-1]) {
            tiles[y][x].addSide(TileSide.LEFT)
        }

        if(x < tiles[y].length-1 && !tiles[y][x+1]) {
            tiles[y][x].addSide(TileSide.RIGHT)
        }

        if(x >= 1 && y >= 1 && !tiles[y-1][x-1]) {
            tiles[y][x].addSide(TileSide.TOP_LEFT)
        }

        if(x < tiles[y].length-1 && y >= 1 && !tiles[y-1][x+1]) {
            tiles[y][x].addSide(TileSide.TOP_RIGHT)
        }
      }
    }
  }
}

function Tile(image, x, y) {
  this.src = image
  this.x = x
  this.y = y
  this.side = 0
}

Tile.prototype.addSide = function (side) {
  this.setSide(this.side | side)
}

Tile.prototype.setSide = function (side) {
  this.side = side
  
  if(this.side == TileSide.TOP) {
      this.x = 32
      this.y = 128
  }
}
