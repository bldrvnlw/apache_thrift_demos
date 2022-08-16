#!/usr/bin/env python

import os
from http.server import CGIHTTPRequestHandler, HTTPServer
import socketserver

PORT = 8081
server_address = ("", PORT)


class Handler(CGIHTTPRequestHandler):
    cgi_directories = ["/"]


print(f"Starting server on port {PORT}...")
with HTTPServer(server_address, Handler) as web_server:
    print("serving at port", PORT)
    web_server.serve_forever()
