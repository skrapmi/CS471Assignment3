# *****************************************************
# This file implements a server for receiving the file
# sent using sendfile(). The server receives a file and
# prints it's contents.
# *****************************************************

import socket
import commands
import SocketServer
import threading
import sys

# The port on which to listen
listenPort = 2345
returnPort = 3456

# Create a welcome socket. 
welcomeSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sendSock    = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
welcomeSock.bind(('', listenPort))
sendSock.bind(('', returnPort))

# Start listening on the socket
welcomeSock.listen(1)
sendSock.listen(1)

print 'Waiting for connection...'

# Accept connections forever
while True:

	# Accept connections
	clientSock, addr   = welcomeSock.accept()
	print 'Accept new connection from %s:%s...' % addr
	
	recieved = clientSock.recv(1024)	
	print "Received: ", recieved
		
	clientSock.send('Handshake FTP...'.encode('utf-8'))
	# The buffer to all data received from the
	# the client.
	fileData = ""

	# The temporary buffer to store the received
	# data.
	recvBuff = ""

	# The size of the incoming file
	fileSize = 0    

	# The buffer containing the file size
	fileSizeBuff = ""

	if recieved == "bob":
		print "we got it now fam"
	
	if recieved == 'get':
		fileName = recvAll(clientSock, 10)

		fileObj = open(fileName, "r")

		fileData = fileObj.read(65536)
		if fileData:
				dataSizeStr = str(len(fileData))

		# The number of bytes sent
		numSent = 0

		while len(dataSizeStr) < 10:
				dataSizeStr = "0" + dataSizeStr

		fileData = dataSizeStr + fileData       

		# The number of bytes sent
		numSent = 0

		# Send the data!
		while len(fileData) > numSent:
				numSent += connSock.send(fileData[numSent:])


	if recieved == "put":
		fileName = recvAll(clientSock, 10)

		# Receive the first 10 bytes indicating the
		# size of the file
		fileSizeBuff = recvAll(clientSock, 10)

		# Get the file size
		fileSize = int(fileSizeBuff)

		print "The file size is ", fileSize

		# Get the file data
		fileData = recvAll(clientSock, fileSize)

		fileObj = open(fileName, "w+")
		fileObj.write(fileData[:fileSize])
		fileObj.close()

	if recieved == " ls":
		for line in commands.getstatusoutput('ls'):
			fileData = fileData + line



	# Close our side
	clientSock.close()


