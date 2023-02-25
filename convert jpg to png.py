from PIL import Image

def convert_jpg_to_png(jpg_filename, png_filename):
    with Image.open(jpg_filename) as im:
        im.save(png_filename, 'PNG')

# Example usage:
convert_jpg_to_png('input.jpg', 'output.png')
