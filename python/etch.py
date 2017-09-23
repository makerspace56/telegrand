import serial
import sys
import pygame
import pygame.camera

pygame.init()
pygame.camera.init()

size = width, height = 640, 480
cam_size = (160, 120)
black = 0, 0, 0
white = 255, 255, 255

screen = pygame.display.set_mode(size)

# this is the same as what we saw before
clist = pygame.camera.list_cameras()
if not clist:
    raise ValueError("Sorry, no cameras detected.")
cam = pygame.camera.Camera(clist[0], cam_size)
cam.start()

def quit():
    cam.stop()
    sys.exit()

# create a surface to capture to.  for performance purposes
# bit depth is the same as that of the display surface.
snapshot = pygame.surface.Surface(cam_size, 0, screen)

x, y = width/2, height/2

with serial.Serial('/dev/ttyACM0', 115200, timeout=1) as ser:
    while 1:
        line = ser.readline()
        if len(line) != 0:
            sx = ord(line[0])
            if sx > 127:
                sx -= 256
            sy = ord(line[1])
            if sy > 127:
                sy -= 256
            sz = ord(line[2])
            screen.set_at((x,y), white)
            pygame.draw.line(screen, white, (x, y), (x + sx, y + sy))
            x += sx
            y += sy
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    quit()
                if event.key == pygame.K_LEFT:
                    x -= 1
                if event.key == pygame.K_RIGHT:
                    x += 1
                if event.key == pygame.K_UP:
                    y -= 1
                if event.key == pygame.K_DOWN:
                    y += 1
                screen.set_at((x,y), white)

        # if you don't want to tie the framerate to the camera, you can check
        # if the camera has an image ready.  note that while this works
        # on most cameras, some will never return true.
        if cam.query_image():
            snapshot = cam.get_image(snapshot)

        # blit it to the display surface.  simple!
        screen.blit(snapshot, (0,0))
        pygame.display.flip()
