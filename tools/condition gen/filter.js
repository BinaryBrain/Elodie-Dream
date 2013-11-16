var output = []

for(var top = 0; top<=1; top++) {
  for(var bottom = 0; bottom<=1; bottom++) {
    for(var right = 0; right<=1; right++) {
      for(var left = 0; left<=1; left++) {
        for(var top_left = 0; top_left<=1; top_left++) {
          for(var top_right = 0; top_right<=1; top_right++) {
            for(var bottom_left = 0; bottom_left<=1; bottom_left++) {
              for(var bottom_right = 0; bottom_right<=1; bottom_right++) {
                
                string = "if(this->side == ("
                
                if (top == 1)
                  string += "(int) TileSide::TOP | "
                if (bottom == 1)
                  string += "(int) TileSide::BOTTOM | "
                if (right == 1)
                  string += "(int) TileSide::RIGHT | "
                if (left == 1)
                  string += "(int) TileSide::LEFT | "
                if (top_left == 1)
                  string += "(int) TileSide::TOP_LEFT | "
                if (top_right == 1)
                  string += "(int) TileSide::TOP_RIGHT | "
                if (bottom_left== 1)
                  string += "(int) TileSide::BOTTOM_LEFT | "
                if (bottom_right == 1)
                  string += "(int) TileSide::BOTTOM_RIGHT | "
                
                string = string.substring(0, string.length - 3)
                string += "))"
                
                if(!((top == 1 && top_left == 1) || (top == 1 && top_right == 1) || (bottom == 1 && bottom_left == 1) || (bottom == 1 && bottom_right == 1) ||
                (left == 1 && top_left == 1) || (left == 1 && bottom_left == 1) || (right == 1 && top_right == 1) || (right == 1 && bottom_right == 1)))
                  output.push(string)
}}}}}}}}

console.log(output.length)

for(var i=0; i<output.length; i++) {
  console.log(output[i])
  console.log("    this->setTextureRect(sf::IntRect(*32, *32, 32, 32));")
}