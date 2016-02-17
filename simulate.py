#!/usr/bin/python2
import sys, pygame, binascii, copy
from shared import *

PIXEL_SIZE = 40
BORDER_SIZE = 4


def DrawPixel(surface, color, x, y):
	assert (0 <= x < DISPLAY_WIDTH), "Position X is out of bounds with value {}!".format(x)
	assert (0 <= y < DISPLAY_HEIGHT), "Position Y is out of bounds with value {}!".format(y)

	# The hardware switches the green and blue channels, so we need to swap the green and blue values.
	massagedColor = FormatPixel(color, (x, y))

	cornerX = (PIXEL_SIZE + BORDER_SIZE) * x
	cornerY = (PIXEL_SIZE + BORDER_SIZE) * y
	area = cornerX, cornerY, PIXEL_SIZE, PIXEL_SIZE
	pygame.draw.rect(surface, massagedColor, area)

def DrawPixelAtIndex(surface, color, index):
	coords = IndexToCoordinates(index)
	DrawPixel(surface, color, coords[0], coords[1])

def DrawImage(surface, imageData):
	for index, pixel in enumerate(imageData):
		DrawPixelAtIndex(surface, pixel, index)

def GetPixelAtScreenCoordinates(xy):
	xCoord = xy[0] / (PIXEL_SIZE + BORDER_SIZE)
	yCoord = xy[1] / (PIXEL_SIZE + BORDER_SIZE) 
	return (xCoord, yCoord)

def ColorPixelAtScreenCoordinates(imageData, screenCoordinates, color):
	pixelToColor = GetPixelAtScreenCoordinates(screenCoordinates)
	modifiedPixelIndex = CoordinatesToIndex(pixelToColor[0], pixelToColor[1])
	imageData[modifiedPixelIndex] = FormatPixel(color, pixelToColor)

def Loop(screen, imageData):
	screen.fill((0, 0, 0))
	DrawImage(screen, imageData)
	pygame.display.flip()

def main(argv):
	assert (len(argv) == 2), "Usage: {} <image filename>".format(argv[0])
	pygame.init()
	filename = argv[1]

	windowSize = DISPLAY_WIDTH * (PIXEL_SIZE + BORDER_SIZE), DISPLAY_HEIGHT * (PIXEL_SIZE + BORDER_SIZE)
	screen = pygame.display.set_mode(windowSize)

	imageData = LoadPixData(filename)
	brushColor = bytearray((0, 0, 0))
	clock = pygame.time.Clock()

	while 1:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					sys.exit()
				elif event.key == pygame.K_s:
					print("Saving to {}".format(filename))
					# TODO: Actually save it.
			if event.type == pygame.QUIT:
				sys.exit()
			if (event.type == pygame.MOUSEMOTION and event.buttons[0] == 1) or (event.type == pygame.MOUSEBUTTONDOWN and event.button == 1):
				ColorPixelAtScreenCoordinates(imageData, event.pos, brushColor)

		Loop(screen, imageData)
		clock.tick(30)


if __name__ == '__main__':
	main(sys.argv)
