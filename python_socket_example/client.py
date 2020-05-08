#! /usn/bin/env python3

import os, sys
import socket

HOST = ''
PORT = 46777

options = { 1:"What is your name?",
			2:"How do you know to respond to these questions?",
			3:"Can I ask you a personal question?",
			4:"Can you answer an arbitrary question?",
			5:"Thank you."	
}

# create an INET, STREAMing socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(HOST, PORT)

selection = 0

while selection != 8:
	print("What would you like to ask the server?")
	print("1. What is your name?")
	print("2. How do you know to respond to these questions?")
	print("3. Can I ask you a personal question?")
	print("4. Can you answer an arbitrary question?")
	print("5. Thank you.")

	# Get user selection
	print("Please enter a choice:")
	selection = int(input())
	if selection not in range(1,6):
		print("I do not understand your question. Please enter a number 1-5.")
		break

	# Send choice to server
	s.send(bytearray(options[selection], 'utf8'))
	data = s.recv(1024)

	# Print results
	print(data.decode('utf8'))
	print()
	break

s.close()
