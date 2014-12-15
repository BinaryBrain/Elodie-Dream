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
images[MAP_GROUND] = "../../assets/img/sprites/tiles/extended/modern/metal.png"
images[MAP_ELODIE] = "../../assets/img/sprites/tiles/extended/field/ground.png"
// images[MAP_GROUND] = "../../assets/img/sprites/tiles/extended/field/ground.png"

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
        if(y >= 1 && !tiles[y-1][x] || y == 0) {
            tiles[y][x].addSide(TileSide.TOP)
        }
        
        if(y < tiles.length-1 && !tiles[y+1][x] || y == tiles.length-1) {
          tiles[y][x].addSide(TileSide.BOTTOM)
        }
        
        if(x >= 1 && !tiles[y][x-1] || x == 0) {
          tiles[y][x].addSide(TileSide.LEFT)
        }
        
        if(x < tiles[y].length-1 && !tiles[y][x+1] || x == tiles[y].length-1) {
          tiles[y][x].addSide(TileSide.RIGHT)
        }
        
        if(x >= 1 && y >= 1 && !tiles[y-1][x-1] || (x == 0 && y == 0)) {
          tiles[y][x].addSide(TileSide.TOP_LEFT)
        }
        
        if(x < tiles[y].length-1 && y >= 1 && !tiles[y-1][x+1] || (x == tiles[y].length-1 && y == 0)) {
          tiles[y][x].addSide(TileSide.TOP_RIGHT)
        }
        
        if(x >= 1 && y < tiles.length-1 && !tiles[y+1][x-1] || (x == 0 && y == tiles.length-1)) {
          tiles[y][x].addSide(TileSide.BOTTOM_LEFT)
        }
        
        if(x < tiles[y].length-1 && y < tiles.length-1 && !tiles[y+1][x+1] || (x == tiles[y].length-1 && y == tiles.length-1)) {
          tiles[y][x].addSide(TileSide.BOTTOM_RIGHT)
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
  
  this.filterSides();

  this.setCoords(0, 0)

  if(this.side == (TileSide.BOTTOM_RIGHT))
    this.setCoords(4*32, 0*32)
  else if(this.side == (TileSide.BOTTOM_LEFT))
    this.setCoords(0*32, 1*32)
  else if(this.side == (TileSide.BOTTOM_LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(4*32, 1*32)
  else if(this.side == (TileSide.TOP_RIGHT))
    this.setCoords(2*32, 0*32)
  else if(this.side == (TileSide.TOP_RIGHT | TileSide.BOTTOM_RIGHT))
    this.setCoords(6*32, 0*32)
  else if(this.side == (TileSide.TOP_RIGHT | TileSide.BOTTOM_LEFT))
    this.setCoords(2*32, 1*32)
  else if(this.side == (TileSide.TOP_RIGHT | TileSide.BOTTOM_LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(6*32, 1*32)
  else if(this.side == (TileSide.TOP_LEFT))
    this.setCoords(1*32, 0*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(5*32, 0*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.BOTTOM_LEFT))
    this.setCoords(1*32, 1*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.BOTTOM_LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(5*32, 1*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.TOP_RIGHT))
    this.setCoords(3*32, 0*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.TOP_RIGHT | TileSide.BOTTOM_RIGHT))
    this.setCoords(7*32, 0*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.TOP_RIGHT | TileSide.BOTTOM_LEFT))
    this.setCoords(3*32, 1*32)
  else if(this.side == (TileSide.TOP_LEFT | TileSide.TOP_RIGHT | TileSide.BOTTOM_LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(7*32, 1*32)
  else if(this.side == (TileSide.LEFT))
    this.setCoords(0*32, 2*32)
  else if(this.side == (TileSide.LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(2*32, 2*32)
  else if(this.side == (TileSide.LEFT | TileSide.TOP_RIGHT))
    this.setCoords(1*32, 2*32)
  else if(this.side == (TileSide.LEFT | TileSide.TOP_RIGHT | TileSide.BOTTOM_RIGHT))
    this.setCoords(3*32, 2*32)
  else if(this.side == (TileSide.RIGHT))
    this.setCoords(0*32, 3*32)
  else if(this.side == (TileSide.RIGHT | TileSide.BOTTOM_LEFT))
    this.setCoords(1*32, 3*32)
  else if(this.side == (TileSide.RIGHT | TileSide.TOP_LEFT))
    this.setCoords(2*32, 3*32)
  else if(this.side == (TileSide.RIGHT | TileSide.TOP_LEFT | TileSide.BOTTOM_LEFT))
    this.setCoords(3*32, 3*32)
  else if(this.side == (TileSide.RIGHT | TileSide.LEFT))
    this.setCoords(0*32, 4*32)
  else if(this.side == (TileSide.BOTTOM))
    this.setCoords(4*32, 3*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.TOP_RIGHT))
    this.setCoords(6*32, 3*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.TOP_LEFT))
    this.setCoords(5*32, 3*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.TOP_LEFT | TileSide.TOP_RIGHT))
    this.setCoords(7*32, 3*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.LEFT))
    this.setCoords(0*32, 5*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.LEFT | TileSide.TOP_RIGHT))
    this.setCoords(1*32, 5*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.RIGHT))
    this.setCoords(6*32, 4*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.RIGHT | TileSide.TOP_LEFT))
    this.setCoords(7*32, 4*32)
  else if(this.side == (TileSide.BOTTOM | TileSide.RIGHT | TileSide.LEFT))
    this.setCoords(4*32, 5*32)
  else if(this.side == (TileSide.TOP))
    this.setCoords(4*32, 2*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM_RIGHT))
    this.setCoords(5*32, 2*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM_LEFT))
    this.setCoords(6*32, 2*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM_LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(7*32, 2*32)
  else if(this.side == (TileSide.TOP | TileSide.LEFT))
    this.setCoords(2*32, 4*32)
  else if(this.side == (TileSide.TOP | TileSide.LEFT | TileSide.BOTTOM_RIGHT))
    this.setCoords(3*32, 4*32)
  else if(this.side == (TileSide.TOP | TileSide.RIGHT))
    this.setCoords(4*32, 4*32)
  else if(this.side == (TileSide.TOP | TileSide.RIGHT | TileSide.BOTTOM_LEFT))
    this.setCoords(5*32, 4*32)
  else if(this.side == (TileSide.TOP | TileSide.RIGHT | TileSide.LEFT))
    this.setCoords(2*32, 5*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM))
    this.setCoords(1*32, 4*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM | TileSide.LEFT))
    this.setCoords(3*32, 5*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM | TileSide.RIGHT))
    this.setCoords(5*32, 5*32)
  else if(this.side == (TileSide.TOP | TileSide.BOTTOM | TileSide.RIGHT | TileSide.LEFT))
    this.setCoords(6*32, 5*32)
}

Tile.prototype.setCoords = function(x, y) {
  this.x = 256-x
  this.y = 192-y
}

Tile.prototype.filterSides = function() {
  if(this.side & TileSide.TOP) {
    this.side = ~(~this.side | TileSide.TOP_LEFT)
    this.side = ~(~this.side | TileSide.TOP_RIGHT)
  }

  if(this.side & TileSide.BOTTOM) {
    this.side = ~(~this.side | TileSide.BOTTOM_LEFT)
    this.side = ~(~this.side | TileSide.BOTTOM_RIGHT)
  }

  if(this.side & TileSide.RIGHT)
    this.side = ~(~this.side | TileSide.TOP_RIGHT)
    this.side = ~(~this.side | TileSide.BOTTOM_RIGHT)

  if(this.side & TileSide.LEFT) {
    this.side = ~(~this.side | TileSide.TOP_LEFT)
    this.side = ~(~this.side | TileSide.BOTTOM_LEFT)
  }
}