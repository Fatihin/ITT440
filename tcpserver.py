<<<<<<< HEAD
from socket import *

bufsize =' '
state = ' '
afterset = ' '
server_socket = socket(AF_INET ,SOCK_STREAM)
=======
import socket
server_socket = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
>>>>>>> 31b0f417cdf5a5442d81bc12401c011932c6e7da
server_socket.bind(("",1025))
server_socket.listen(5)

print "TCPServer Waiting for client on port 1025"

while 1:
	client_socket, address = server_socket.accept()
	print "I got a connection from ", address
	while 1:
		data = raw_input ("SEND (TYPE q or Q to Quit):")
		if (data == 'Q' or data == 'q'):
			client_socket.send(data)
			client_socket.close()
			break;
		else:
<<<<<<< HEAD
			
			client_socket.send(data)
			bufsize = client_socket.getsockopt(SOL_SOCKET, SO_SNDBUF)
			state = client_socket.getsockopt(SOL_SOCKET, SO_REUSEADDR)
			data = client_socket.recv(512)
			print "buffer send :" , bufsize
			print "reuse address before set :", state
=======
			client_socket.send(data)
			data = client_socket.recv(512)
>>>>>>> 31b0f417cdf5a5442d81bc12401c011932c6e7da
		if (data == 'q' or data == 'Q'):
			client_socket.close()
			break;
		else:
<<<<<<< HEAD
			afterset = client_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR,1)
			
			print "reuse after set:", client_socket.getsockopt(SOL_SOCKET,SO_REUSEADDR)

=======
			print "RECEIVED:", data
>>>>>>> 31b0f417cdf5a5442d81bc12401c011932c6e7da
			
