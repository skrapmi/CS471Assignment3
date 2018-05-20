from ftplib import FTP
import socket

#Test credentials
FTP_server = 'ftp.dlptest.com'
FTP_user   = 'dlpuser@dlptest.com'
FTP_pass   = 'eiTqR7EMZD5zy7M'

FTP_server_pub = 'ftp.uconn.edu'
FTP_port_pub   = '21';

ftp = FTP(FTP_server)
ftp.login(user = FTP_user, passwd = FTP_pass)

def getFile():

	filename = ''
	localfile = open(filename, 'wb')
	ftp.retrbinary('RETR ' + filename, localfile.write, 1024)
	
	ftp.quit()
	localfile.close()
	
def placeFile():

	filename = ''
	ftp.storbinary('STOR ' + filename, open(filename, 'rb'))
	ftp.quit()
	
placeFile()


def menuSelection():

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
