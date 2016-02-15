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
	pixData = []

	r, g, b = im.split()
	for i in range(TOTAL_PIXELS):
		coords = IndexToCoordinates(i)
		rVal = r.getpixel(coords)
		gVal = g.getpixel(coords)
		bVal = b.getpixel(coords)

		pixData.append(FormatPixel(rVal, gVal, bVal, coords))

	return pixData


def ConvertToPix(imageFilename):
	im = Image.open(imageFilename)

	# Scale image if it is too small or big
	im = ScaleImage(im, DISPLAY_WIDTH, DISPLAY_HEIGHT)
	pixData = ConvertDataToPix(im)
	return pixData


def FixRGBInPixFile(filename):
	imageData = LoadPixData(filename)

	# Hitting everything with FormatPixel() should fix everything.
	for i in range(TOTAL_PIXELS):
		coords = IndexToCoordinates(i)
		currentPixel = imageData[i]
		imageData[i] = FormatPixel(currentPixel[0], currentPixel[2], currentPixel[1], coords)

	return imageData


def main(argv):
	assert (len(argv) > 1), "Usage: {} <image1> <image2> ... <imageN>".format(argv[0])

	for imageFilename in argv[1:]:
		if imageFilename.endswith(".pix"):
			# We are just fixing the RGB order.
			print("Finagling RGB orders in " + imageFilename)
			outputFilename = imageFilename
			pixData = FixRGBInPixFile(imageFilename)
		else:
			outputFilename = os.path.splitext(imageFilename)[0] + ".pix"
			print("Converting to " + outputFilename)
			pixData = ConvertToPix(imageFilename)

		WritePixData(outputFilename, pixData)


if __name__ == '__main__':
	main(sys.argv)
