# coding=utf-8

import pygame

# pygame initial
pygame.init()

# configure
tWindowSize = (400, 300)
nRectX = 30
nRectY = 30
tRectColor = (64, 224, 208)
rWindowBGColor = (0, 0, 0)
tRectInfo = (nRectX, nRectY, 60, 60)
sWindowCaption = "pygame first test"
bFinish = False

# make surface
myPyGame = pygame.display.set_mode(tWindowSize)

pygame.display.set_caption(sWindowCaption)

# main thread
while not bFinish:
    for eEvent in pygame.event.get():
        # event handling

        pressedKey = pygame.key.get_pressed()
        if eEvent.type == pygame.QUIT:
            bFinish = True

    # check key
    #pressedKey = pygame.key.get_pressed()
    if pressedKey[pygame.K_UP]   : nRectY -= 3
    if pressedKey[pygame.K_DOWN] : nRectY += 3
    if pressedKey[pygame.K_RIGHT]: nRectX += 3
    if pressedKey[pygame.K_LEFT] : nRectX -= 3

    # check state

    # draw

    myPyGame.fill(rWindowBGColor)
    pygame.draw.rect(myPyGame, tRectColor, pygame.Rect(nRectX, nRectY, 60, 60))
    pygame.display.flip()

    # frame setting
    pygame.time.Clock().tick(60)


