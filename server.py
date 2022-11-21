#!/usr/bin/env python3
import ssl
import sys
from http.server import HTTPServer, SimpleHTTPRequestHandler


class CORSRequestHandler(SimpleHTTPRequestHandler):
    extensions_map = {
        '.manifest': 'text/cache-manifest',
        '.html': 'text/html',
        '.png': 'image/png',
        '.jpg': 'image/jpg',
        '.svg': 'image/svg+xml',
        '.css': 'text/css',
        '.js': 'application/x-javascript',
        '': 'application/octet-stream',  # Default
    }

    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        SimpleHTTPRequestHandler.end_headers(self)


def main():
    httpd = HTTPServer(('0.0.0.0', int(sys.argv[1]) if len(sys.argv) > 1 else 8443), CORSRequestHandler)
    httpd.socket = ssl.wrap_socket(httpd.socket, keyfile="key.pem", certfile='cert.pem', server_side=True)
    httpd.serve_forever()


if __name__ == '__main__':
    main()
