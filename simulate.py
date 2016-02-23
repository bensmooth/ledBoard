#!/usr/bin/python2
import sys, pygame, binascii, copy
from shared import *

PIXEL_SIZE = 40
BORDER_SIZE = 4
COLOR_PICKER_HEIGHT = 40

def DrawPixel(surface, color, x, y):
	assert (0 <= x < DISPLAY_WIDTH), "Position X is out of bounds with value {}!".format(x)
	assert (0 <= y < DISPLAY_HEIGHT), "Position Y is out of bounds with value {}!".format(y)

	# The hardware switches the green and blue channels, so we need to swap the green and blue values.
	massagedColor = FormatPixel(color, (x, y))

	cornerX = (PIXEL_SIZE + BORDER_SIZE) * x
	cornerY = (PIXEL_SIZE + BORDER_SIZE) * y
	area = cornerX, cornerY, PIXEL_SIZE, PIXEL_SIZE
	pygame.draw.rect(surface, massagedColor, area)

def GetPixelAtScreenCoordinates(xy):
	xCoord = xy[0] / (PIXEL_SIZE + BORDER_SIZE)
	yCoord = xy[1] / (PIXEL_SIZE + BORDER_SIZE) 
	return (xCoord, yCoord)

class DrawingScene:
	def __init__(self, initialImageData, backgroundColor, initialBrushColor):
		self.imageData = initialImageData
		self.fontRenderer = pygame.font.SysFont("monospace", 42)
		self.backgroundColor = backgroundColor
		self.brushColor = initialBrushColor
		self.drawableGridArea = DISPLAY_WIDTH * (PIXEL_SIZE + BORDER_SIZE), DISPLAY_HEIGHT * (PIXEL_SIZE + BORDER_SIZE)
		self.totalArea = self.drawableGridArea[0], self.drawableGridArea[1] + COLOR_PICKER_HEIGHT

	def OnLoop(self, screen):
		screen.fill(self.backgroundColor)

		colorText = "({}, {}, {})".format(*self.brushColor)
		colorTextSurface = self.fontRenderer.render(colorText, True, (230, 230, 230), self.backgroundColor)
		screen.blit(colorTextSurface, (0, screen.get_height() - colorTextSurface.get_height()))
		self.DrawImage(screen)

	def HandleMouseClick(self, clickCoordinates):
		# See if this is even in the area that we care about.
		areaWeCareAbout = pygame.Rect((0, 0), self.drawableGridArea)
		if not areaWeCareAbout.collidepoint(clickCoordinates):
			return

		# Color the pixel that was clicked on.
		pixelToColor = GetPixelAtScreenCoordinates(clickCoordinates)
		modifiedPixelIndex = CoordinatesToIndex(pixelToColor[0], pixelToColor[1])
		self.imageData[modifiedPixelIndex] = FormatPixel(self.brushColor, pixelToColor)

	def DrawPixelAtIndex(self, surface, color, index):
		coords = IndexToCoordinates(index)
		DrawPixel(surface, color, coords[0], coords[1])

	def DrawImage(self, surface):
		for index, pixel in enumerate(self.imageData):
			self.DrawPixelAtIndex(surface, pixel, index)


def main(argv):
	assert (len(argv) == 2), "Usage: {} <image filename>".format(argv[0])
	filename = argv[1]
	pygame.init()

	initialImageData = LoadPixData(filename)
	drawingScene = DrawingScene(initialImageData, pygame.Color("Black"), pygame.Color("Black"))

	clock = pygame.time.Clock()
	screen = pygame.display.set_mode(drawingScene.totalArea)

	while 1:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				keys = pygame.key.get_pressed()
				if keys[pygame.K_ESCAPE]:
					sys.exit()
				elif keys[pygame.K_LCTRL]:
					if keys[pygame.K_s]:
						print("Saving to {}".format(filename))
						WritePixData(filename, drawingScene.imageData)
				else:
					# TODO: Handle color picker typing here.
					print("Pressed a key")
			if event.type == pygame.QUIT:
				sys.exit()
			if (event.type == pygame.MOUSEMOTION and event.buttons[0] == 1) or (event.type == pygame.MOUSEBUTTONDOWN and event.button == 1):
				drawingScene.HandleMouseClick(event.pos)

		drawingScene.OnLoop(screen)

		pygame.display.flip()

		clock.tick(30)


if __name__ == '__main__':
	main(sys.argv)
