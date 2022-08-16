An Apache Thrift test based on the example in chapter 3
"Learning Apache Thrift", Krzysztof Rakowski, ISBN 978-1-78588-274-6 

The code was made to run with thrift 0.16 (installed from conan-center) on Windows 
with VisualStudio 2019.

The client and server have been written in C++ using the Apache Thrift cpp tutorial
to fill in the gaps (https://github.com/apache/thrift/tree/master/tutorial/cpp)



Generate cpp client and server interfaces, templatized methods and full include paths

thrift --gen cpp:templates,include_prefix myfirst.thrift