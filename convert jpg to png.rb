require 'chunky_png'
require 'mini_magick'

def convert_jpg_to_png(jpg_filename, png_filename)
  # Read the JPG image data
  image = MiniMagick::Image.open(jpg_filename)

  # Convert to PNG format using ChunkyPNG
  png_data = ChunkyPNG::Image.from_io(StringIO.new(image.to_blob)) 

  # Write the PNG data to a file
  File.open(png_filename, 'wb') do |file|
    png_data.write(file)
  end
end
