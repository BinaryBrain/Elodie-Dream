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
				ctx.clearRect(0, 0, ctx.width, ctx.height);
				$('#resultImage').css("height", h);
				$('#resultImage').css("width", w);
				$('#resultImage').css("background", "url("+image+")");
				$('#hbCan').attr("height", h);
				$('#hbCan').attr("width", w);
			}
		})(file);
			
		// For data URI purposes
		fileReader.readAsDataURL(file);
	} else {
		var fileReader = new FileReader();
		fileReader.onload = (function(file) {
			return function(e) { 
				var content = this.result;
				ctx.clearRect(0, 0, ctx.width, ctx.height);
				$('#jsonInput').val(content); 
				drawFromJson();
			}
		})(file);
		fileReader.readAsText(file);
	}
  }
  
  function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}


  function handleDragOver(evt) {
    evt.stopPropagation();
    evt.preventDefault();
    evt.dataTransfer.dropEffect = 'copy'; // Explicitly show this is a copy.
  }
  
  function drawFromJson() {
	try {
		var obj = JSON.parse($('#jsonInput').val());
		ctx.clearRect(0, 0, ctx.width, ctx.height);
	} catch(err) {
		$("#jsonMessage").html("Your JSON is probably not correct : \n"+err.message);
		ctx.clearRect(0, 0, ctx.width, ctx.height);
		return;
	}
	$('#hbCan').attr("width", $('#hbCan').attr("width"));
	$("#jsonMessage").html(" ");
	var height = obj.height;
	var width = obj.width;
	var anim = obj.anim;
	ctx.clearRect(0, 0, ctx.width, ctx.height);
	var a = $("#alpha").val()/10.0;
	var c = hexToRgb($("#hbColor").val());
	ctx.fillStyle = 'rgba('+c.r+', '+c.g+', '+c.b+', '+a+')';
	var animNumber = 0;
	anim.forEach(function(stance) {	
		console.log(stance);
		for (frame = 0; frame < stance.hitbox.length; frame++) {
			var x1 = width*frame+stance.hitbox[frame][0];
			var y1 = height*animNumber+stance.hitbox[frame][1];
			var w = stance.hitbox[frame][2]-stance.hitbox[frame][0];
			var h = stance.hitbox[frame][3]-stance.hitbox[frame][1];
			console.log(x1 + ", " + y1 + ", " + w + ", " + h);
			ctx.fillRect(x1, y1, w, h);
		}
		animNumber++;
	});
  }
  // Setup the dnd listeners.
  var dropZone = document.getElementById('container');
  dropZone.addEventListener('dragover', handleDragOver, false);
  dropZone.addEventListener('drop', handleFileSelect, false);
  
  $('#jsonInput').bind('input propertychange', function(){
	drawFromJson();
  });
  $('#alpha').bind('input propertychange', function(){
	drawFromJson();
  });
  $('#hbColor').bind('input propertychange', function(){
	drawFromJson();
  });
  ctx = document.getElementById('hbCan').getContext("2d");
  ctx.clearRect(0, 0, ctx.width, ctx.height);
} else {
  alert('The File APIs are not fully supported in this browser.');
}