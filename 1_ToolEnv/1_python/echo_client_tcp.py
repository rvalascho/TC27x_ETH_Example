import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('10.0.0.191', 7)
print >>sys.stderr, 'connecting to %s port %s' % server_address
sock.connect(server_address)

try:
  message = 'Send me an ADC Value'
  # Send data
  print >>sys.stderr, 'sending "%s"' % message
  sock.sendall(message)

  # Receive response
  amount_received = 0
  amount_expected = 4 #len(message)

  while amount_received < amount_expected:
    data = sock.recv(4)
    amount_received += len(data)
    print >>sys.stderr, 'received "%s"' % data

finally:
  print >>sys.stderr, 'closing socket'
  sock.close()

