#!/usr/bin/python2
import sys, pygame, binascii, copy
from shared import *

def DrawPixel(surface, color, x, y):
	assert (0 <= x < DISPLAY_WIDTH), "Position X is out of bounds with value {}!".format(x)
	assert (0 <= y < DISPLAY_HEIGHT), "Position Y is out of bounds with value {}!".format(y)

	# The hardware switches the green and blue channels, se we need to swap the green and blue values.
	massagedColor = copy.deepcopy(color)
	massagedColor[1] = color[2]
	massagedColor[2] = color[1]

	cornerX = (PIXEL_SIZE + BORDER_SIZE) * x
	cornerY = (PIXEL_SIZE + BORDER_SIZE) * y
	area = cornerX, cornerY, PIXEL_SIZE, PIXEL_SIZE
	pygame.draw.rect(surface, massagedColor, area)

def DrawPixelAtIndex(surface, color, index):
	coords = IndexToCoordinates(index)
	print("coords={}".format(coords))
	DrawPixel(surface, color, coords[0], coords[1])

def LoadImage(filename):
	f = open(filename, "rb")

	try:
		# Suck entire file in.
		fileContents = bytearray(f.read())
		fileContentsLength = len(fileContents)
		assert (fileContentsLength % 3 == 0), "Length of file ({}) must be a multiple of 3!".format(fileContentsLength)

		# Split into RBG tuples.
		data = [fileContents[i:i+3] for i in range(0, fileContentsLength, 3)]

		return data
	finally:
		f.close()

def DrawImage(surface, imageData):
	for index, pixel in enumerate(imageData):
		DrawPixelAtIndex(surface, pixel, index)

def main(argv):
	assert (len(argv) == 2), "Usage: {} <image filename>".format(argv[0])
	pygame.init()

	windowSize = DISPLAY_WIDTH * (PIXEL_SIZE + BORDER_SIZE), DISPLAY_HEIGHT * (PIXEL_SIZE + BORDER_SIZE)
	screen = pygame.display.set_mode(windowSize)

	screen.fill((0, 0, 0))

	imageData = LoadImage(argv[1])

	print("imageData = '{}' of '{}'".format(type(imageData), type(imageData[0])))
	print([binascii.hexlify(bytearray(x)) for x in imageData])

	DrawImage(screen, imageData)

	pygame.display.flip()

	while 1:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					sys.exit()
			if event.type == pygame.QUIT:
				sys.exit()

if __name__ == '__main__':
	main(sys.argv)