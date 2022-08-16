// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "MyFirstService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class MyFirstServiceHandler : virtual public MyFirstServiceIf {
 public:
  MyFirstServiceHandler() {
    // Your initialization goes here
  }

  void ping() {
    // Your implementation goes here
    printf("ping\n");
  }

  void log(const std::string& filename) {
    // Your implementation goes here
    printf("log\n");
  }

  int32_t multiply(const int32_t number1, const int32_t number2) {
    // Your implementation goes here
    printf("multiply\n");
  }

  int32_t get_log_size(const std::string& filename) {
    // Your implementation goes here
    printf("get_log_size\n");
  }

  void send_binary(const std::string& blob, const std::string& filename) {
    // Your implementation goes here
    printf("send_binary\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<MyFirstServiceHandler> handler(new MyFirstServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new MyFirstServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
