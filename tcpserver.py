from socket import *

bufsize =' '
state = ' '
afterset = ' '
server_socket = socket(AF_INET ,SOCK_STREAM)
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
			
			client_socket.send(data)
			bufsize = client_socket.getsockopt(SOL_SOCKET, SO_SNDBUF)
			state = client_socket.getsockopt(SOL_SOCKET, SO_REUSEADDR)
			data = client_socket.recv(512)
			print "buffer send :" , bufsize
			print "reuse address before set :", state
		if (data == 'q' or data == 'Q'):
			client_socket.close()
			break;
		else:
			afterset = client_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR,1)
			
			print "reuse after set:", client_socket.getsockopt(SOL_SOCKET,SO_REUSEADDR)

			
