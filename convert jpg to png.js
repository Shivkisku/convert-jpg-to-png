function convertJpgToPng(jpgUrl, pngUrl, callback) {
    var img = new Image();
    img.onload = function() {
      var canvas = document.createElement('canvas');
      canvas.width = img.width;
      canvas.height = img.height;
      var ctx = canvas.getContext('2d');
      ctx.drawImage(img, 0, 0);
      canvas.toBlob(function(blob) {
        var xhr = new XMLHttpRequest();
        xhr.open('POST', pngUrl);
        xhr.setRequestHeader('Content-Type', 'image/png');
        xhr.onload = function() {
          if (xhr.status === 200) {
            if (typeof callback === 'function') {
              callback();
            }
          } else {
            console.error('Error:', xhr.statusText);
          }
        };
        xhr.send(blob);
      }, 'image/png');
    };
    img.onerror = function() {
      console.error('Error: Could not load image:', jpgUrl);
    };
    img.src = jpgUrl;
  }
  