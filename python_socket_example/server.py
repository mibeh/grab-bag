#! /usn/bin/env python3

import os, sys
import socket

HOST = ''
PORT = 46777

options = { "What is your name?":"Ultron",
			"How do you know to respond to these questions?":"I programmed this.",
			"Can I ask you a personal question?":"No, you can't.",
			"Can you answer an arbitrary question?":"Yes, I can, but I won't.",
			"Thank you.":"You're welcome. Have a nice day!"	
}

# create an INET, STREAMing socket
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# bind the socket to a public host, and a well-known port
serversocket.bind((socket.gethostname(), PORT))
# become a server socket
serversocket.listen(5)

while True:
    # accept connections from outside
    (clientsocket, address) = serversocket.accept()
    print('Connection recieved from '+ str(address))
    # now do something with the clientsocket
    # in this case, we'll pretend this is a threaded server

    data = clientsocket.recv(1024).decode('utf8')
    if not data:
    	break

    clientsocket.send(bytearray(options[data], 'utf8'))
    print('Sending "'+options[data]+'" to the client.')
    clientsocket.close()



serversocket.close()
