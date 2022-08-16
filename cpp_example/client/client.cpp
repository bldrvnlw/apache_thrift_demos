#include <iostream>
#include <random>
#include <filesystem>
#include <fstream>
#include <thread>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TPipe.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/MyFirstService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main(int argc, char* argv[]) {
    // thrift will prepend the required \\\\.\\pipe\\ to the name on Windows
    std::string pipe_name("puffthemagicpipe"); 
    if (argc >= 2) {
        pipe_name = std::string(argv[1]);
    }

    std::shared_ptr<TBinaryProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    std::shared_ptr<TTransport> socket(new TPipe(pipe_name));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(protocolFactory->getProtocol(transport));

    // Cleaning up the client releases the pipe (which is a file shared with the pipeserver) allowing completion of the last command
    {
        auto client = std::make_unique<MyFirstServiceClient>(protocol);
        transport->open();
        try {


            client->ping();
            client->log("logfile.txt");
            std::cout << "ping()" << endl;
            std::random_device rd;  //Seed for the random number engine
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1, 100);
            auto number1 = distrib(gen);
            auto number2 = distrib(gen);
            std::cout << number1 << " * " << number2 << " = " << client->multiply(number1, number2) << endl;
            std::cout << "Log file size " << client->get_log_size("logfile.txt") << endl;

            std::filesystem::path binsource = "D:\\Projects\\apache_thrift\\cpp_example\\build\\Release\\20200518_081705.jpg";
            auto infile = std::ifstream{ binsource, std::ios::binary | std::ios::in };
            auto send_buf = std::string(std::istreambuf_iterator<char>(infile), {});
            std::cout << "bigtext.txt, size: " << send_buf.size() << " bytes" << endl;
            client->send_binary(send_buf, std::string{ "newpic.jpg" });
            client->send_binary(send_buf, std::string{ "newpic2.jpg" });
            client->send_binary(send_buf, std::string{ "newpic3.jpg" });
        }
        catch (TException& tx) {
            std::cout << "ERROR: " << tx.what() << endl;
        }
        // client is destroyed here
    }


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

}
