#!/usr/bin/python3
from PIL import ImageFont, Image, ImageDraw
import sys, string

imageMode = "1"


def main(argv):
	assert (len(argv) == 2), "Usage: {} <font file>".format(argv[0])
	fontFilename = argv[1]
	className = input("Enter font class name: ")

	# use a bitmap font
	if fontFilename.endswith(".ttf"):
		fontSize = int(input("Enter font point size: "))
		font = ImageFont.truetype(fontFilename, 15)
	else:
		font = ImageFont.load(fontFilename)

	# Open our output file, and write header.
	outfile = open(className + ".h", "w")

	letters = string.ascii_letters + string.digits + string.punctuation + " \t"

	renderedSize = GetFontRenderSize(font, letters)
	print("Using bitmapped font size: {}".format(renderedSize))

	WriteHeader(outfile, className, fontFilename, renderedSize)

	for letter in letters:
		if letter == '\'' or letter == '\\':
			caseValue = "\\" + letter
		else:
			caseValue = letter;

		WriteLine(outfile, "		case '{}':".format(caseValue))
		im = RenderLetter(font, letter, renderedSize)
		WriteBitmap(outfile, im)

	WriteFooter(outfile, renderedSize)

	outfile.close()

	return 0

def GetFontRenderSize(font, letters):
	width = 1
	height = 1

	for letter in letters:
		letterDimensions = font.getsize(letter)
		width = max(width, letterDimensions[0])
		height = max(height, letterDimensions[1])

	return (width, height)


def RenderLetter(font, letter, renderSize):
	backgroundColor = 0
	foregroundColor = 1

	image = Image.new(imageMode, renderSize, backgroundColor)
	draw = ImageDraw.Draw(image)

	draw.text((0, 0), letter, font=font, fill=foregroundColor)

	bbox = image.getbbox()
	#cropped = image.crop(bbox)
	#print("Resizing image of {} from {} to: {}".format(letter, image.size, cropped.size))

	#cropped.save("{}.png".format(letter))

	# For now, return non-cropped image.
	return image


def WriteLine(filehandle, line):
	filehandle.write(line + "\n")

def WriteHeader(outfile, className, fontFilename, bitmapDim):
	WriteLine(outfile, "#include <array>")
	WriteLine(outfile, "")
	WriteLine(outfile, "")
	WriteLine(outfile, "namespace Pix")
	WriteLine(outfile, "{")
	WriteLine(outfile, "// Generated from: {}".format(fontFilename))
	WriteLine(outfile, "class {}".format(className))
	WriteLine(outfile, "{")
	WriteLine(outfile, "")
	WriteLine(outfile, "public:")
	WriteLine(outfile, "	typedef std::array<std::array<bool, {}>, {}> FontBitmapType;".format(bitmapDim[0], bitmapDim[1]))
	WriteLine(outfile, "")
	WriteLine(outfile, "	// The number of pixels after each letter.")
	WriteLine(outfile, "	static constexpr uint16_t SpacingPixels = 0;")
	WriteLine(outfile, "")
	WriteLine(outfile, "	static constexpr uint16_t LetterHeight = std::tuple_size<FontBitmapType>::value;")
	WriteLine(outfile, "	static constexpr uint16_t LetterWidth = std::tuple_size<FontBitmapType::value_type>::value;")
	WriteLine(outfile, "")
	WriteLine(outfile, "	static constexpr FontBitmapType GetCharacterBitmap(char c)")
	WriteLine(outfile, "	{")
	WriteLine(outfile, "		switch (c)")
	WriteLine(outfile, "		{")


def WriteBitmap(outfile, bitmap):
	# What we are going for:
	#				{1, 1, 1},

	width = bitmap.size[0]
	height = bitmap.size[1]

	WriteLine(outfile, "			return FontBitmapType")
	WriteLine(outfile, "			{{")

	for y in range(0, height):
		outfile.write("				{")
		for x in range(0, width):
			if bitmap.getpixel((x, y)) == 0:
				outfile.write("0")
			else:
				outfile.write("1")

			if x != (width - 1):
				outfile.write(", ")

		outfile.write("},\n")

	WriteLine(outfile, "			}};")


def WriteFooter(outfile, bitmapDim):
	WriteLine(outfile, "		default:")
	allWhite = Image.new(imageMode, bitmapDim, 1)
	WriteBitmap(outfile, allWhite)
	WriteLine(outfile, "		}")
	WriteLine(outfile, "	}")
	WriteLine(outfile, "};")
	WriteLine(outfile, "")
	WriteLine(outfile, "}")


if __name__ == '__main__':
	main(sys.argv)
