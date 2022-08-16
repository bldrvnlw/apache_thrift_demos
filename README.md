### Apache Thrift demos

Some apache thrift tests based on the book "Learning Apache Thrift", Krzysztof Rakowski, ISBN 978-1-78588-274-6 and the Apache tutorials on GitHub.

The goals was to have a pure C++ based client and server that would run on Windows over named pipes

1. learning_at_ch3: Modified from the book example for windows
2. cpp_example: The book example rewritten using cpp and named Pipes on windows


Thrift was installed from conan-center and both the release and debug libraries (for Windows MSVC 2019) placed in sub-directory thrift_0_16 containing bin, lib, include directories