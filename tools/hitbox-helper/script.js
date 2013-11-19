// Check for the various File API support.
if (window.File && window.FileReader && window.FileList && window.Blob) {
  // TODO
} else {
  alert('The File APIs are not fully supported in this browser.');
}