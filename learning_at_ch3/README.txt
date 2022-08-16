An Apache Thrift test based on the example in chapter 3
"Learning Apache Thrift", Krzysztof Rakowski, ISBN 978-1-78588-274-6 

The code was made to run with thrift 0.16 (installed from conan-center) on Windows 
with VisualStudio 2019.
Php8.1 was installed using chocolatey.


How to generate py and php interfaces

..\thrift_0_16\bin\thrift.exe --gen py --gen php:server myfirst.thrift