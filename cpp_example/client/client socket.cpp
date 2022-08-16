#include <iostream>
#include <random>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/MyFirstService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main() {
  std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  MyFirstServiceClient client(protocol);

  try {
    transport->open();

    client.ping();
    client.log("logfile.txt");
    cout << "ping()" << endl;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 100);
    auto number1 = distrib(gen);
    auto number2 = distrib(gen);
    cout << number1 << " * " << number2 << " = " << client.multiply(number1, number2) << endl;

    //Work work;
    //work.op = Operation::DIVIDE;
    //work.num1 = 1;
    //work.num2 = 0;

    //try {
    //  client.calculate(1, work);
    //  cout << "Whoa? We can divide by zero!" << endl;
    //} catch (InvalidOperation& io) {
    //  cout << "InvalidOperation: " << io.why << endl;
    //  // or using generated operator<<: cout << io << endl;
    //  // or by using std::exception native method what(): cout << io.what() << endl;
    //}

    //work.op = Operation::SUBTRACT;
    //work.num1 = 15;
    //work.num2 = 10;
    //int32_t diff = client.calculate(1, work);
    //cout << "15 - 10 = " << diff << endl;

    //// Note that C++ uses return by reference for complex types to avoid
    //// costly copy construction
    //SharedStruct ss;
    //client.getStruct(ss, 1);
    //cout << "Received log: " << ss << endl;

    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}
