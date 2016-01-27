#!/usr/bin/python2
import sys, pygame, binascii, copy
from shared import *

PIXEL_SIZE = 40
BORDER_SIZE = 4


def DrawPixel(surface, color, x, y):
	assert (0 <= x < DISPLAY_WIDTH), "Position X is out of bounds with value {}!".format(x)
	assert (0 <= y < DISPLAY_HEIGHT), "Position Y is out of bounds with value {}!".format(y)

	# The hardware switches the green and blue channels, so we need to swap the green and blue values.
	massagedColor = copy.deepcopy(color)
	massagedColor[1] = color[2]
	massagedColor[2] = color[1]

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

def GetPixelAtScreenCoordinates(x, y):
	# TODO: ?
	return (0, 0)

def Loop(screen, imageData):
	screen.fill((0, 0, 0))
	DrawImage(screen, imageData)
	pygame.display.flip()

def main(argv):
	assert (len(argv) == 2), "Usage: {} <image filename>".format(argv[0])
	pygame.init()

	windowSize = DISPLAY_WIDTH * (PIXEL_SIZE + BORDER_SIZE), DISPLAY_HEIGHT * (PIXEL_SIZE + BORDER_SIZE)
	screen = pygame.display.set_mode(windowSize)

	imageData = LoadPixImage(argv[1])
	brushColor = (0, 0, 0)

	while 1:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					sys.exit()
			if event.type == pygame.QUIT:
				sys.exit()
			if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
				pixelToColor = GetPixelAtScreenCoordinates(0, 0)
				

		Loop(screen, imageData)


if __name__ == '__main__':
	main(sys.argv)
