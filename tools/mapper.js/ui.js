$(function () {
  if (!window.File || !window.FileReader || !window.FileList || !window.Blob) {
    alert('The File APIs are not fully supported in this browser.')
  } else {
    function handleFileSelect(evt) {
      evt.stopPropagation();
      evt.preventDefault();

      var files = evt.dataTransfer.files; // FileList object.
      
      for (var i = 0, f; f = files[i]; i++) {
        // Only process image files.
        if (!f.type == 'text/plain') {
          alert("Please send a text/plain level")
          continue;
        }

        var reader = new FileReader();

        // Closure to capture the file information.
        reader.onload = (function(fi) {
          return function(e) {
            $("#input").val(e.target.result);
            $("#filename").html(fi.name)
            refresh();
          };
        })(f);

        // Read in the image file as a data URL.
        reader.readAsText(f);
      }
    }
    
    function handleDragOver(evt) {
      evt.stopPropagation();
      evt.preventDefault();
      evt.dataTransfer.dropEffect = 'copy'; // Explicitly show this is a copy.
    }

    // Setup the dnd listeners.
    var dropZone = $('#input').get(0);
    dropZone.addEventListener('dragover', handleDragOver, false);
    dropZone.addEventListener('drop', handleFileSelect, false);
  }
  
  var level = "                        \n"+
              "                        \n"+
              "  E             ########\n"+
              "##########  ############\n"+
              "########################"
  
  $("#input").text(level)
  
  var text = level
  
  $("#input").bind("keyup paste", function () {
    if ($(this).val() != text) {
        text = $(this).val()
    }
    
    refresh()
  })
  
  refresh()
})

function refresh() {
  level = $("#input").val()
  
  var tiles = []
  var entities = []
  
  parse(level, tiles, entities)
  beautify(tiles)
  
  var html = ""
  for(var y = 0; y<tiles.length; y++) {
    html += '<div class="line">'
    for(var x = 0; x<tiles[y].length; x++) {
      if(tiles[y][x] !== undefined)
        html += '<div style="background: url('+tiles[y][x].src+') '+tiles[y][x].x+'px '+tiles[y][x].y+'px;" class="tile"></div>'
      else
        html += '<div class="tile"></div>'
    }
    html += '</div>'
  }
  
  $("#output").html(html);
}