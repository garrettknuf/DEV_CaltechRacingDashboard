from PIL import Image
import math

"""****************** UPDATE THESE PARAMS FOR YOUR IMAGE ********************"""
image_path = 'CaltechRacingLogo.png'
output_file_path = 'caltech_racing_logo_data.txt'
width = 435
height = 87
"""**************************************************************************"""

if __name__ == "__main__":

    # Open image
    img = Image.open(image_path)

    # Resize to desired size
    img = img.resize((width, height))
    
    # Rotate image
    img = img.rotate(270, expand=True)

    # Flip image horizontally
    img = img.transpose(Image.FLIP_LEFT_RIGHT)

    # Make sure in RGB mode
    img = img.convert('RGB')

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

    # Pad data array so that there is not an odd number of pixels
    if (len(pixel_list) % 2 != 0):
        pixel_list += '000'

    # Data array stores pixel data in byte format that will be sent over SPI
    # Each byte: 0-0-r1-g1-b2-r2-g2-b2
    data_arr = "\t"

    # Concatenate string that will consist of bytes for data array
    for i in range((int)(math.ceil(len(pixel_list) / 6))):
        # First two MSBs are not used
        # "0b" indicates a binary value
        data_arr += "0b00"

        # Add the 3-bit RGB values for two pixels in the six (6) LSBs
        data_arr += pixel_list[i * 6 : i * 6 + 6]

        # Only add command after byte if it is not the last byte
        if i != (len(pixel_list) / 6) - 1:
            data_arr += ", "
            # New line and indent often to not exceed character limit per line
            if (i+1) % 10 == 0:
                data_arr += '\n\t'

    # Print data as variable in c syntax
    output = "static uint8_t caltech_racing_logo_img[" \
                + (str)((int)(len(pixel_list) / 6)) + "] = {\n"
    output += data_arr
    output += "};"

    # Write string output to text file
    # The output can be copied and pasted into codebase
    with open(output_file_path, 'w') as file:
        file.write(output)