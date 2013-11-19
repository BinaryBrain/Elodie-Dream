// Check for the various File API support.
if (window.File && window.FileReader && window.FileList && window.Blob) {
  function handleFileSelect(evt) {
    evt.stopPropagation();
    evt.preventDefault();

    var files = evt.dataTransfer.files; // FileList object.
	
	if (files[0].type.match('image.*')) {
		var fileReader = new FileReader();
		fileReader.onload = (function(file) {
			return function(e) { 
				// Push the data URI into an array
				//dataArray.push({name : file.name, value : this.result});

				// This is the image
				var image = this.result;
				var w = file.width;
				var h = file.height;
				$('#resultImage').append('<div class="image" style="height: '+h+'; width: '+w+'; background: url('+image+'); "> </div>'); 
			}

			
		})(files[0]);
			
		// For data URI purposes
		fileReader.readAsDataURL(files[0]);
		document.getElementById('resultImage').innerHTML = '<ul>' + '1' + '</ul>';
	}
	
	
  }

  function handleDragOver(evt) {
    evt.stopPropagation();
    evt.preventDefault();
    evt.dataTransfer.dropEffect = 'copy'; // Explicitly show this is a copy.
  }

  // Setup the dnd listeners.
  var dropZone = document.getElementById('container');
  dropZone.addEventListener('dragover', handleDragOver, false);
  dropZone.addEventListener('drop', handleFileSelect, false);
} else {
  alert('The File APIs are not fully supported in this browser.');
}