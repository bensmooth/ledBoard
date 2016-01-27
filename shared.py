DISPLAY_WIDTH = 18
DISPLAY_HEIGHT = 18
TOTAL_PIXELS = DISPLAY_WIDTH * DISPLAY_HEIGHT

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
	y = position // DISPLAY_WIDTH

	if (y % 2 == 1):
		# Odd rows go backwards
		x = DISPLAY_WIDTH - 1 - x

	return (x, y)

# Given an RGB tuple and coordinates, converts the RGB tuple into an RBG tuple if necessary.
def FormatPixel(r, g, b, coordinates):
	# The hardware requires us to use RGB instead of RBG for the last row.
	if coordinates[1] == (DISPLAY_HEIGHT - 1):
		return (r, g, b)
	else:
		return (r, b, g)


# Loads a PIX image file into memory as an array of RGB triplets.
def LoadPixImage(filename):
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
