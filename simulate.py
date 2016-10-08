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
		self.pixelGridArea = DISPLAY_WIDTH * (PIXEL_SIZE + BORDER_SIZE), DISPLAY_HEIGHT * (PIXEL_SIZE + BORDER_SIZE)
		self.totalArea = self.pixelGridArea[0], self.pixelGridArea[1] + COLOR_PICKER_HEIGHT

	def OnLoop(self, screen):
		screen.fill(self.backgroundColor)

		colorText = "({}, {}, {})".format(*self.brushColor)
		colorTextSurface = self.fontRenderer.render(colorText, True, (230, 230, 230), self.backgroundColor)
		screen.blit(colorTextSurface, (0, screen.get_height() - colorTextSurface.get_height()))
		self.DrawImage(screen)

		# Color in the pixel that the mouse is currently hovering over.
		if pygame.mouse.get_focused():
			self.ColorPixelAtScreenCoordinates(screen, pygame.mouse.get_pos(), False)

	def ColorPixelAtScreenCoordinates(self, screen, screenCoordinates, updateImage):
		# Are these screen coordinates even in the drawing area?
		drawableArea = pygame.Rect((0, 0), self.pixelGridArea)
		if not drawableArea.collidepoint(screenCoordinates):
			return

		# Figure out which pixel is being selected.
		pixelToColor = GetPixelAtScreenCoordinates(screenCoordinates)
		selectedPixelIndex = CoordinatesToIndex(*pixelToColor)
		self.DrawPixelAtIndex(screen, self.brushColor, selectedPixelIndex)
		if updateImage:
			self.imageData[selectedPixelIndex] = FormatPixel(self.brushColor, pixelToColor)

	def HandleMouseClick(self, screen, clickCoordinates):
		self.ColorPixelAtScreenCoordinates(screen, clickCoordinates, True)

	def DrawPixelAtIndex(self, surface, color, index):
		coords = IndexToCoordinates(index)
		DrawPixel(surface, color, coords[0], coords[1])

	def DrawImage(self, surface):
		for index, pixel in enumerate(self.imageData):
			self.DrawPixelAtIndex(surface, pixel, index)


def main(argv):
	assert (len(argv) == 2), "Usage: {} <image filename>".format(argv[0])
	filename = argv[1]
	pygame.font.init()
	clock = pygame.time.Clock()

	initialImageData = LoadPixData(filename)
	drawingScene = DrawingScene(initialImageData, pygame.Color("Black"), pygame.Color("Black"))

	pygame.display.set_caption("LED Board Simulator - {}".format(filename), filename)
	screen = pygame.display.set_mode(drawingScene.totalArea)

	nextColorString = ""

	while 1:
		drawingScene.OnLoop(screen)

		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					sys.exit()
				elif event.key == pygame.K_s and event.mod & pygame.KMOD_CTRL:
					print("Saving to {}".format(filename))
					WritePixData(filename, drawingScene.imageData)
				else:
					if event.key == pygame.K_RETURN:
						print("Attempting to set brush color to '{}'".format(nextColorString))
						try:
							drawingScene.brushColor = pygame.Color(nextColorString)
							print("Brush color set to {}".format(drawingScene.brushColor))
						except ValueError as exception:
							print(str(exception))

						nextColorString = ""
					else:
						keyName = pygame.key.name(event.key)
						if event.key == pygame.K_3 and event.mod & pygame.KMOD_SHIFT:
							nextColorString += "#"
						elif len(keyName) == 1:
							nextColorString += keyName
						else:
							print("Unhandled key: {}".format(keyName))

			if event.type == pygame.QUIT:
				sys.exit()
			if ((event.type == pygame.MOUSEMOTION) and (event.buttons[0] == 1)) or ((event.type == pygame.MOUSEBUTTONDOWN and event.button == 1)):
				drawingScene.HandleMouseClick(screen, event.pos)

		pygame.display.flip()

		clock.tick(30)


if __name__ == '__main__':
	main(sys.argv)
