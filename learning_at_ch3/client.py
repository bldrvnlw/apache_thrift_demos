#!/usr/bin/env python

import sys, glob

sys.path.append("gen-py")

from myfirst import MyFirstService

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport, THttpClient
from thrift.protocol import TBinaryProtocol

from random import randint

try:

    # socket = TSocket.TSocket("localhost", "8080")  #  '/MyFirstServer.php'
    socket = THttpClient.THttpClient("http://localhost:8081/MyFirstServer.bat")
    transport = TTransport.TBufferedTransport(socket)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = MyFirstService.Client(protocol)
    transport.open()

    # calling log method
    client.log("logfile.log")
    print("logged current time to logfile (not waiting for response)")

    # calling multiply method with random parameters
    number1 = randint(1, 100)
    number2 = randint(1, 100)
    product = client.multiply(number1, number2)
    print(f"{number1}x{number2}={product}")

    # calling get_log_size method
    print(f"current size of logfile is: {client.get_log_size('logfile.log')} Bytes")

    # calling get_log_size method second time, but this time with wrong parameter
    print(
        f"current size of logfile is: {client.get_log_size('no_such_file.log')} Bytes"
    )

    transport.close()

except Thrift.TException as e:
    print(
        f"Received following error:\n error code: {e.error_code}\n error desc: {e.error_description}"
    )
