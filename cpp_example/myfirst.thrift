// namespaces are used in resulting packages
namespace php myfirst
namespace py myfirst

// you can define names for your types.
// Usable primarily for integers.
// Bad idea for cpp int is a keyword
// typedef i32 int

// simple exception
exception MyError {
	1: i32 error_code,
	2: string error_description
}

// here starts the service definition - 3 methods
service MyFirstService {
	// are we communicating?
	void ping(),

	// log method - it saves timestamp to given file
	oneway void log(1:string filename),

	// multiply method - returns result of multiplication of two integers; it returns integer as well
	i32 multiply(1:i32 number1, 2:i32 number2),

	// get_log_size method - returns size of log file; throws exception when problems occur
	i32 get_log_size(1:string filename) throws (1:MyError error),

	// send a binary blob (thrift encodes these as a special case of string )
	oneway void send_binary(1:binary blob, 2:string filename),
}