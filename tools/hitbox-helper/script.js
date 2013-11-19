// Check for the various File API support.
if (window.File && window.FileReader && window.FileList && window.Blob) {
  function handleFileSelect(evt) {
    evt.stopPropagation();
    evt.preventDefault();

    var file = evt.dataTransfer.files[0]; // FileList object.
	
	if (file.type.match('image.*')) {
		var fileReader = new FileReader();
		fileReader.onload = (function(file) {
			return function(e) { 
				var imgSymbolic = new Image();
				var image = this.result;
				imgSymbolic.src = image;
				var w = imgSymbolic.width;
				var h = imgSymbolic.height;
				$('#resultImage').html('<div class="image" style="height: '+h+'px; width: '+w+'px; background: url('+image+'); border: solid 1px"><canvas id="hbCan" width="'+w+'" height="'+h+'"></canvas></div>'); 
			}
		})(file);
			
		// For data URI purposes
		fileReader.readAsDataURL(file);
	} else {
		var fileReader = new FileReader();
		fileReader.onload = (function(file) {
			var content = this.result;
			alert(this);
			$('#jsonInput').val(content); 
		})(file);
		fileReader.readAsText(file);
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