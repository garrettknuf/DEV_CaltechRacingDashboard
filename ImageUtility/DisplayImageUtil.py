from PIL import Image
import math

"""Update these params for your image"""
image_path = 'CaltechRacingLogo.png'
output_file_path = 'caltech_racing_logo_data.txt'
width = 435
height = 87

if __name__ == "__main__":

    # Open image
    img = Image.open(image_path)

    # Resize to desired size
    img = img.resize((width, height))
    
    # Rotate and flip
    img = img.rotate(270, expand=True)
    img = img.transpose(Image.FLIP_LEFT_RIGHT)

    # Make sure in RGB mode
    img = img.convert('RGB')

    img.save('img_output.jpg')

    # Initialize empty pixel data list
    pixel_list = ""

    # Iterate through the RGB value of each pixel in the image
    width, height = img.size
    print("Width: " + (str)(width))
    print("Height: " + (str)(height))
    for y in range(height):
        for x in range(width):
            # Get RGB values
            r, g, b = img.getpixel((x, y))
            
            # Convert 8-bit RGB to 3-bit RGB
            pixel_list += ('1' if r >= 127 else '0')
            pixel_list += ('1' if g >= 127 else '0')
            pixel_list += ('1' if b >= 127 else '0')

    if (len(pixel_list) % 2 != 0):
        pixel_list += '000'

    # Data array stores pixel data in byte format that will be sent over SPI
    # Each byte: 0-0-r1-g1-b2-r2-g2-b2
    data_arr = "\t"

    for i in range((int)(math.ceil(len(pixel_list) / 6))):
        data_arr += "0b00"
        data_arr += pixel_list[i*6 : i*6 + 6]

        if i != (len(pixel_list) / 6) - 1:
            data_arr += ", "
            if (i+1) % 10 == 0:
                data_arr += '\n\t'

    # Print data as variable in c syntax
    output = "static uint8_t caltech_racing_logo_img[" + (str)((int)(len(pixel_list) / 6)) + "] = {\n"
    output += data_arr
    output += "};"

    with open(output_file_path, 'w') as file:
        file.write(output)
