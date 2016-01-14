#!/usr/bin/python2
import sys, os
from PIL import Image
from shared import *

def ScaleImage(im, x, y):
	if im.width != DISPLAY_WIDTH or im.height != DISPLAY_HEIGHT:
		return im.resize((x, y))
	else:
		return im

def ForceRGB(im):
	if im.mode != "RGB":
		print("Converting from {} to RGB".format(im.mode))
		im = im.convert("RGB")

	return im

def ConvertDataToPix(im):
	im = ForceRGB(im)
	pixData = bytearray()

	r, g, b = im.split()
	for i in range(TOTAL_PIXELS):
		coords = IndexToCoordinates(i)
		rVal = r.getpixel(coords)
		gVal = g.getpixel(coords)
		bVal = b.getpixel(coords)
		# Intentionally changing order of b and g, to match hardware.
		pixData.append(rVal)
		pixData.append(bVal)
		pixData.append(gVal)

	return pixData

def ConvertToPix(imageFilename, outputFilename):
        im = Image.open(imageFilename)

        # Scale image if it is too small or big
        im = ScaleImage(im, DISPLAY_WIDTH, DISPLAY_HEIGHT)

        pixData = ConvertDataToPix(im)

        outfile = open(outputFilename, "wb")
        try:
                outfile.write(pixData)
        finally:
                outfile.close()

def main(argv):
	assert (len(argv) > 1), "Usage: {} <image1> <image2> ... <imageN>".format(argv[0])

	for imageFilename in argv[1:]:
		outputFilename = os.path.splitext(imageFilename)[0] + ".pix"
		print("Converting to " + outputFilename)
		ConvertToPix(imageFilename, outputFilename)

if __name__ == '__main__':
	main(sys.argv)
