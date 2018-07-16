__version__ = "0.3"

__all__ = ["HTTPServer", "BaseHTTPRequestHandler"]

import sys
import time
import socket # For gethostbyaddr()
import mimetools
import SocketServer
import xml.dom.minidom

# Default error message
DEFAULT_ERROR_MESSAGE = ""

g=[None]*1000

class HTTPServer(SocketServer.ThreadingTCPServer):

#    allow_reuse_address = 1    # Seems to make sense in testing environment
    
#    self.daemon_threads=true;
    def server_bind(self):
        """Override server_bind to store the server name."""
        SocketServer.TCPServer.server_bind(self)
        host, port = self.socket.getsockname()[:2]
        self.server_name = socket.getfqdn(host)
        self.server_port = port


class BaseHTTPRequestHandler(SocketServer.StreamRequestHandler):   
    def server_activate(self):        
        self.socket.listen(1000)    
#    def socket_write(self,wfile,string):
#        wfile.write(string)
    def handle_one_request(self):
        global g        
#        print help(self.rfile)
        try:
            raw_requestline = self.rfile.readline()            
            if not raw_requestline:
                self.close_connection = 1
                return                    
            if raw_requestline[-2:] == '\r\n':
                raw_requestline = raw_requestline[:-2]
            elif raw_requestline[-1:] == '\n':
                raw_requestline = raw_requestline[:-1]
            print raw_requestline
            dom1=xml.dom.minidom.parseString(raw_requestline)        
            for t in dom1.childNodes:
                if t._attrs.has_key('Name'):
                    if self.rsaname=='' and t.getAttribute('Name')!='':
                        self.rsaname=t.getAttribute('Name')
                        if t.getAttribute('NickName')!='':
                            self.nickName=t.getAttribute('NickName')
                        found=0
                        for i in range(0,1000):
                            if g[i]==self:
                                found=1
                                print 'found befor'
                                break                                            
                        if found==1:break;
                        for i in range(0,1000):
                            if (g[i] is None):
                                self.gIndex=i
                                g[self.gIndex]=self                                                                                
                                break                                            
                elif t._attrs.has_key('GetFriendList'):
                    impl = xml.dom.minidom.getDOMImplementation()                    
                    newdoc = impl.createDocument(None, "Msg", None)
                    top_element = newdoc.documentElement
                    friends=newdoc.createElement('FriendList')
                    top_element.appendChild(friends)                    
                    for i in range(0,1000):
                        if (g[i] is None):continue;                            
                        friend =newdoc.createElement('Friend')
                        friend.setAttribute('Name',g[i].rsaname);
                        friend.setAttribute('NickName',g[i].nickName);
                        friends.appendChild(friend);                    
                    s=newdoc.toxml() 
                    s=s.replace('\r\n','');
                    s=s.replace('\n','');
                    s=s+'\r\n';
                    #socket_write(self.wfile,s)
                    self.wfile.write(s)
                    print s 
                elif t._attrs.has_key('From'):
                    if t.getAttribute('From')=='' or t.getAttribute('To')=='':continue;
                    sto=t.getAttribute('To')
                    for i in range(0,1000):
                        if (g[i] is None):continue;                    
                        if(g[i].rsaname!=sto):                       
                            continue;
                        else:
                            pass 
                        s=raw_requestline
                        s=s.replace('\r\n','');
                        s=s.replace('\n','');
                        s=s+'\r\n';           
                        g[i].wfile.write(s)
                        #socket_write(g[i].wfile,s)
                #self.wfile.write(s)
                #From
                    
##                            for i in range(0,1000):
##                                if gName[i]!='':
##                                    s=s+','+gName[i]
##                            s=s+'\r\n'
##                            print 'c',s                    
        except Exception,e:
            self.close_connection = 1
            print e;
            if self.gIndex>=0:
                g[self.gIndex]=None
                self.gIndex=-1
                return                  
 
    def handle(self):
        self.rsaname=''
        self.nickName=''
        self.gIndex=-1
        global g
        """Handle multiple requests if necessary."""
        self.close_connection = 0        
        self.handle_one_request()
        while not self.close_connection:
            self.handle_one_request()
        print self.gIndex
        if self.gIndex>=0:
            g[self.gIndex]=None
#        print 'Out',g


def test(HandlerClass = BaseHTTPRequestHandler,
         ServerClass = HTTPServer, protocol="HTTP/1.0"):
    """Test the HTTP request handler class.

    This runs an HTTP server on port 8000 (or the first command line
    argument).

    """

    if sys.argv[1:]:
        port = int(sys.argv[1])
    else:
        port = 8877
    server_address = ('', port)
    
    HandlerClass.protocol_version = protocol    
    httpd = ServerClass(server_address, HandlerClass)    
    httpd.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sa = httpd.socket.getsockname()
    print "Serving HTTP on", sa[0], "port", sa[1], "..."
    httpd.serve_forever()


if __name__ == '__main__':
    test()
