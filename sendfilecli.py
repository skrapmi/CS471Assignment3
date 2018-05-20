# *******************************************************************
# This file illustrates how to send a file using an
# application-level protocol where the first 10 bytes
# of the message from client to server contain the file
# size and the rest contain the file data.
# *******************************************************************
import socket
import os
import sys
import thread

# Command line checks 
#if len(sys.argv) < 2 or type(sys.argv[1]) != int:
#    print "USAGE python " + "<server_name>" + " <port_number>" 
#    sys.exit()

# Server address
serverAddr = sys.argv[1]

# Server port
serverPort = sys.argv[2]

# Create a TCP socket
connSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
#connSock.connect((serverAddr, serverPort)) 

def getFile(fileName):
    # Connect to the server
    #connSock.connect((serverAddr, serverPort))
    
    # Close the socket and the file
    connSock.close()

def putFile(fileName):
    # Connect to the server
    connSock.connect(('localhost', int(serverPort)))

    # The number of bytes sent
    numSent = 0

    # The file data
    fileData = None

    # Open the file
    fileObj = open(fileName, "r")

    # Keep sending until all is sent
    # Read 65536 bytes of data
    fileData = fileObj.read(65536)

    # Make sure we did not hit EOF
    if fileData:
        # Get the size of the data read
        # and convert it to string
        dataSizeStr = str(len(fileData))

        # Prepend 0's to the size string
        # until the size is 10 bytes
        while len(dataSizeStr) < 10:
            dataSizeStr = "0" + dataSizeStr

        # Prepend 0's to the name string
        # until the size is 10 bytes
        while len(fileName) < 10:
            fileName = "0" + fileName

        # Prepend the size of the data to the
        # file data.
        fileData = "put" + fileName  + dataSizeStr + fileData

        # The number of bytes sent
        numSent = 0

        # Send the data!
        while len(fileData) > numSent:
            numSent += connSock.send(fileData[numSent:])

    print "Sent ", numSent, " bytes."

    # Close the socket and the file
    connSock.close()
    fileObj.close()


def ls():
    # Connect to the server
    connSock.connect((serverAddr, int(serverPort)))
    connSock.send(" ls")

    # Close the socket
    connSock.close()

def lls():
    for line in commands.getstatusoutput('ls -l'):
        print line    

def exiting():
    pass

cont = True
while cont:
    response =  raw_input("ftp> ")
    input_list = response.split()

    if (input_list[0] == 'get'):
        getFile(input_list[1])

    elif (input_list[0] == 'put'):
        putFile(input_list[1])

    elif (input_list[0] == 'ls'):
        ls()

    elif (input_list[0] == 'lls'):
        lls()

    elif (input_list[0] == 'quit'):
        exiting()
        cont = False

    else:
        print "Invalid command"

def serverStart():
    returnPort = 3456
    returnSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    returnSock.bind(('', returnPort))

    while True:
	returnSock.listen(1)
	
	clientSock, addr = returnSock.accept()

	fileData = ""
	recvBuff = ""
	fileSize = 0
	fileSizeBuff = ""

	fileSize = int(recvAll(clientSock, 10))
	fileName = returnedFile.txt
	fileObj = open(fileName, "w+")
	fileData = recAll(clientSock, fileSize)
	fileObj.write(fileData[:fileSize])
	fileObj.close()
	returnSock.close()
	delay(10)


def recvAll(sock, numBytes):

    recvBuff = ""
    tmpBuff  = ""
    while len(recvBuff) < numBytes:

	tmpBuff = sock.recv(numBytes)
	if not tmpBuff:
	    break

	recvBuff += tmpBuff

    return recvBuff


t1 = Thread(target = serverStart)
t1.start()
