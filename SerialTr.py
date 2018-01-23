import serial
# import matrice
import time
import cv2 as cv
import numpy as np
import sys
import curses
import sys,tty,termios

# img = cv.imread('/home/mihai/Downloads/index.jpeg')
# img = cv.imread('/home/mihai/Downloads/img2.png')

class _Getch:
    def __call__(self):
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(3)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch

class Command:

	def __init__(self, port, baud, scale, debug=None):
		self.port = port
		self.baud = baud
		self.scale = scale
		self.debug = debug

		self.ser = serial.Serial(self.port, self.baud, timeout=1)

		if self.ser.isOpen():
			print(self.ser.name + ' is open...')

	def enableDebug(self):
		self.debug = 1

	def disableDebug(self):
		self.debug = None

	def move(self, position, wait=0.1):
		command = 'G1 X' + str(position[0] * self.scale) + ' Y' + str(position[1] * self.scale)
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		time.sleep(wait)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

	def down(self):
		time.sleep(0.2)
		command = 'G2 Z0'
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		time.sleep(0.2)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

		command = 'G2 Z0'
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		time.sleep(0.2)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

	def up(self):
		time.sleep(0.2)
		command = 'G2 Z1'
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		time.sleep(0.2)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

		command = 'G2 Z1'
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		time.sleep(0.2)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

	def calibreUp(self):
		# time.sleep(0.2)
		command = 'G2 I1'
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		# time.sleep(0.2)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

	def calibreDown(self):
		# time.sleep(0.2)
		command = 'G2 I0'
		if self.debug:
			print('\t cmd = ' + command)
		self.ser.write(command.encode('ascii') + '\r\n')
		# time.sleep(0.2)
		out = self.ser.readline()
		if self.debug:
			print('Receiving... ' + out)

	def close(self):
		self.move((0,0), wait=1)
		self.ser.close()

port = '/dev/ttyACM0'
baud = 9600

# matrix = [
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0],
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
# ]

# matrix = [
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0],
#     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
# 	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0],

# matrix = [
#     [0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
# ]

# open the serial port
# ser = serial.Serial(port, baud, timeout=1)

def manhattanDistance(currentPos, destinationPos):
    xy1 = currentPos
    xy2 = destinationPos
    return abs(xy1[0] - xy2[0]) + abs(xy1[1] - xy2[1])

def euclideanDistance(currentPos, destinationPos):
    xy1 = currentPos
    xy2 = destinationPos
    return ( (xy1[0] - xy2[0]) ** 2 + (xy1[1] - xy2[1]) ** 2 ) ** 0.5

def searchMatrix(matrix):
	posArray = []
	for i in range(len(matrix)):
		for j in range(len(matrix[i])):
			if matrix[i][j] != 0:
				posArray.append((i/4,j/4))
				print('Pos = ', i, j)

	ppDist = 300

	# c = Command(port, baud, 3, debug = 1)

	currentPos = (0, 0)

	c.up()
	while posArray:
		min = 300
		destinationPos = currentPos
		for i in posArray:
			d = euclideanDistance(currentPos, i)
			if d < min:
				min = d
				destinationPos = i
		posArray.remove(destinationPos)
		currentPos = destinationPos


		# print('min = ', min)
		if min > 2 and ppDist < 2:
			c.up()
		elif min < 2 and ppDist > 2:
			c.down()
		ppDist = min
		c.move(destinationPos)

	c.up()
	c.close()

def typeCommand():
	ser = serial.Serial(port, baud, timeout=1)

	if ser.isOpen():
		print(ser.name + ' is open...')

	while True:
		cmd = input("Enter command or 'exit': ")

		if cmd == 'exit':
			ser.close()
			exit()
		else:
			ser.write(cmd.encode('ascii') + '\r\n')
			out = ser.readline()
			while out:
				print('Receiving... ' + out)
				out = ser.readline()

def setup():
	# c = Command(port, baud, 1)
	# event = None
	#
	# screen = curses.initscr()
	# try:
	# 	curses.noecho()
	# 	curses.curs_set(0)
	# 	screen.keypad(1)
	# 	screen.addstr("Press a key")
	# 	event = screen.getch()
	# finally:
	# 	curses.endwin()
	#
	# while event != 27:
	# 	# event = None
	# 	try:
	# 		curses.noecho()
	# 		curses.curs_set(0)
	# 		screen.keypad(1)
	# 		screen.addstr("Press a key")
	# 		event = screen.getch()
	# 	finally:
	# 		curses.endwin()
	# 	if event == curses.KEY_UP:
	# 		c.calibreUp()
	# 		# print("Left Arrow Key pressed")
	# 	elif event == curses.KEY_DOWN:
	# 		c.calibreDown()
	# 		print("Right Arrow Key pressed")
	# 	else:
	# 	    print(event)
	# c.up()
	while True:
		k = get()
		if k == 'up':
			c.calibreUp()
		if k == 'down':
			c.calibreDown()
		if k == 'right':
			break
	# c.up()

def get():
	inkey = _Getch()
	while(1):
		k=inkey()
		if k!='':break
	if k=='\x1b[A':
		print "up"
		return "up"
	elif k=='\x1b[B':
		print "down"
		return "down"
	elif k=='\x1b[C':
		print "right"
		return "right"
	elif k=='\x1b[D':
		print "left"
		return "left"
	elif k == '\x1b[Q':
		print "quit"
		return "quit"

def sendFile(filename):
    ser = serial.Serial(port, baud, timeout=1)
    with open(filename) as f:
        for cmd in f:
            if cmd[0] == 'G' or cmd[0] == 'M':
                ser.write(cmd.encode('ascii') + '\r\n')
                print(cmd)
                if (cmd[0] == 'M'):
                    time.sleep(0.5)
                    ser.write(cmd.encode('ascii') + '\r\n')
                    time.sleep(0.5)
                else:
                    time.sleep(0.5)
                # time.sleep(0.3)
                out = ser.readline()
                # while out:
                #     print('Receiving... ' + out)
                #     out = ser.readline()

c = Command(port, baud, 3, debug = 1)

if sys.argv[1] == 'img':
    img = cv.imread(sys.argv[2])
    edges = cv.Canny(img, 100, 200)
    cv.imshow('image', edges)
    cv.waitKey(0)
    searchMatrix(edges)
elif sys.argv[1] == 'cmd':
	typeCommand()
elif sys.argv[1] == 'setup':
	# c.disableDebug()
    setup()
    searchMatrix(edges)
elif sys.argv[1] == 'file':
    sendFile(sys.argv[2])
