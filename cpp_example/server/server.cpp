/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TPipeServer.h>
#include <thrift/transport/TPipe.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "../gen-cpp/MyFirstService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

class MyFirstServiceHandler : public MyFirstServiceIf {
public:
  MyFirstServiceHandler() = default;

  void ping() override { cout << "ping()" << endl; }

  int32_t multiply(const int32_t n1, const int32_t n2) override {
    cout << "add(" << n1 << ", " << n2 << ")" << endl;
    return n1 * n2;
  }

  void log(const std::string& filename) {
    std::time_t now = std::time(nullptr);
    std::ofstream{ filename, std::ios::app } << std::ctime(&now) << "\n";
  }

  int32_t get_log_size(const std::string& filename) {
    // Your implementation goes here
    std::filesystem::path logfile = filename;
    std::error_code ec;
    std::uintmax_t size = std::filesystem::file_size(logfile, ec);
    return static_cast<int32_t>(size);
  }

  void send_binary(const std::string& blob, const std::string& filename) {
      cout << "Recieved blob with name " << filename << "\n";
      // Your implementation goes here
      std::filesystem::path logfile = filename;
      auto out = std::ofstream{ filename, std::ios::binary | std::ios::trunc | std::ios::out };
      cout << "Writing " << blob.size() << " bytes to " << filename << "\n";
      for (auto b : blob) {
          out << b;
      }
      
  }
/*   int32_t calculate(const int32_t logid, const Work& work) override {
    cout << "calculate(" << logid << ", " << work << ")" << endl;
    int32_t val;

    switch (work.op) {
    case Operation::ADD:
      val = work.num1 + work.num2;
      break;
    case Operation::SUBTRACT:
      val = work.num1 - work.num2;
      break;
    case Operation::MULTIPLY:
      val = work.num1 * work.num2;
      break;
    case Operation::DIVIDE:
      if (work.num2 == 0) {
        InvalidOperation io;
        io.whatOp = work.op;
        io.why = "Cannot divide by 0";
        throw io;
      }
      val = work.num1 / work.num2;
      break;
    default:
      InvalidOperation io;
      io.whatOp = work.op;
      io.why = "Invalid Operation";
      throw io;
    }

    SharedStruct ss;
    ss.key = logid;
    ss.value = to_string(val);

    log[logid] = ss;

    return val;
  }

  void getStruct(SharedStruct& ret, const int32_t logid) override {
    cout << "getStruct(" << logid << ")" << endl;
    ret = log[logid];
  }

  void zip() override { cout << "zip()" << endl; } */

protected:
  //map<int32_t, SharedStruct> log;
};

/*MyFirstServiceIfFactory is code generated.
  MyFirstServiceCloneFactory is useful for getting access to the server side of the
  transport.  It is also useful for making per-connection state.  Without this
  CloneFactory, all connections will end up sharing the same handler instance.
*/
class MyFirstServiceCloneFactory : virtual public MyFirstServiceIfFactory {
 public:
  ~MyFirstServiceCloneFactory() override = default;
  MyFirstServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) override
  {
    std::shared_ptr<TPipe> pipe = std::dynamic_pointer_cast<TPipe>(connInfo.transport);
    cout << "Incoming connection\n";
    cout << "\tPipeName: "  << pipe->getPipename() << "\n";
    cout << "\tPipeTimeout: "    << pipe->getConnTimeout() << "\n";
    return new MyFirstServiceHandler;
  }
  void releaseHandler(MyFirstServiceIf* handler) override {
    delete handler;
  }
};

int main(int argc, char* argv[]) {
    std::string pipe_name("puffthemagicpipe");
    if (argc >= 2) {
        pipe_name = std::string(argv[1]);
    }
    // single threaded server with pipe instead of socket
    TThreadedServer server(
      std::make_shared<MyFirstServiceProcessorFactory>(std::make_shared<MyFirstServiceCloneFactory>()),
      std::make_shared<TPipeServer>(pipe_name, 1024, 10),
      //std::make_shared<TServerSocket>(9090), //port
      std::make_shared<TBufferedTransportFactory>(),
      std::make_shared<TBinaryProtocolFactory>());

  /*
  // if you don't need per-connection state, do the following instead
  TThreadedServer server(
    std::make_shared<CalculatorProcessor>(std::make_shared<CalculatorHandler>()),
    std::make_shared<TServerSocket>(9090), //port
    std::make_shared<TBufferedTransportFactory>(),
    std::make_shared<TBinaryProtocolFactory>());
  */

  /**
   * Here are some alternate server types...

  // This server only allows one connection at a time, but spawns no threads
  TSimpleServer server(
    std::make_shared<CalculatorProcessor>(std::make_shared<CalculatorHandler>()),
    std::make_shared<TServerSocket>(9090),
    std::make_shared<TBufferedTransportFactory>(),
    std::make_shared<TBinaryProtocolFactory>());

  const int workerCount = 4;

  std::shared_ptr<ThreadManager> threadManager =
    ThreadManager::newSimpleThreadManager(workerCount);
  threadManager->threadFactory(
    std::make_shared<ThreadFactory>());
  threadManager->start();

  // This server allows "workerCount" connection at a time, and reuses threads
  TThreadPoolServer server(
    std::make_shared<CalculatorProcessorFactory>(std::make_shared<CalculatorCloneFactory>()),
    std::make_shared<TServerSocket>(9090),
    std::make_shared<TBufferedTransportFactory>(),
    std::make_shared<TBinaryProtocolFactory>(),
    threadManager);
  */

  cout << "Starting the server..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}
