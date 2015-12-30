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
	assert (im.mode == "RGB"), "Unknown mode {}".format(im.mode)
	return im

def ConvertToPix(im):
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

def main(argv):
	assert (len(argv) == 2), "Usage: {} <image to convert>".format(argv[0])

	inputFilename = argv[1]
	im = Image.open(inputFilename)

	# Scale image if it is too small or big
	im = ScaleImage(im, DISPLAY_WIDTH, DISPLAY_HEIGHT)

	pixData = ConvertToPix(im)

	outfile = open(inputFilename + ".pix", "wb")
	try:
		outfile.write(pixData)
	finally:
		outfile.close()


if __name__ == '__main__':
	main(sys.argv)