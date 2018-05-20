# *****************************************************
# This file implements a server for receiving the file
# sent using sendfile(). The server receives a file and
# prints it's contents.
# *****************************************************

import socket
import commands

# The port on which to listen
listenPort = sys.argv[1]

# Create a welcome socket. 
welcomeSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
welcomeSock.bind(('', listenPort))

# Start listening on the socket
welcomeSock.listen(1)

# ************************************************
# Receives the specified number of bytes
# from the specified socket
# @param sock - the socket from which to receive
# @param numBytes - the number of bytes to receive
# @return - the bytes received
# *************************************************
def recvAll(sock, numBytes):

	# The buffer
	recvBuff = ""

	# The temporary buffer
	tmpBuff = ""

	# Keep receiving till all is received
	while len(recvBuff) < numBytes:

		# Attempt to receive bytes
		tmpBuff =  sock.recv(numBytes)

		# The other side has closed the socket
		if not tmpBuff:
				break

		# Add the received bytes to the buffer
		recvBuff += tmpBuff

	return recvBuff

# Accept connections forever
while True:

	print "Waiting for connections..."

	# Accept connections
	clientSock, addr = welcomeSock.accept()

	print "Accepted connection from client: ", addr , " on socket " , clientSock
	print "\n"

	#connSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	#connSock.connect((addr, clientSock))

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

	commandBuff = recvAll(clientSock, 3)

	if commandBuff == 'get':
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


	if commandBuff == 'put':
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

	if commandBuff == ' ls':
		import os
		os.system('ls')
		for line in commands.getstatusoutput('ls'):
			#fileData = fileData + line



	# Close our side
	clientSock.close()


