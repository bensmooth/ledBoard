#!/usr/bin/python2
import sys, pygame, binascii, copy

DISPLAY_WIDTH = 9
DISPLAY_HEIGHT = 5
TOTAL_PIXELS = DISPLAY_WIDTH * DISPLAY_HEIGHT
PIXEL_SIZE = 50
BORDER_SIZE = 5

# Converts a set of coordinates into an index.
def CoordinatesToIndex(x, y):
	index = y * DISPLAY_WIDTH

	if (y % 2 == 0):
		index = index + x
	else:
		index = index + DISPLAY_WIDTH - x

	return index

# Converts an index to coordinates as it would appear on the board. 9x5 example:
# 0    1    2    3    4    5    6    7    8
# 17   16   15   14   13   12   11   10   9
# 18   19   20   21   22   23   24   25   26
# 35   34   33   32   31   30   29   28   27
# 36   37   38   39   40   41   42   43   44
def IndexToCoordinates(position):
	assert (0 <= position < TOTAL_PIXELS), "Index is out of range with value {}".format(position)
	x = position % DISPLAY_WIDTH
	y = position / DISPLAY_WIDTH

	if (y % 2 == 1):
		# Odd rows go backwards
		x = DISPLAY_WIDTH - 1 - x

	return (x, y)

def DrawPixel(surface, color, x, y):
	assert (0 <= x < DISPLAY_WIDTH), "Position X is out of bounds with value {}!".format(x)
	assert (0 <= y < DISPLAY_HEIGHT), "Position Y is out of bounds with value {}!".format(y)

	# Because the hardware says so, we need to swap the green and blue values.
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