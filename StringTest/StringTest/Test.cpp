#include "../../String.h"
#include <string>
#include <iostream>

using String = LLD::String;
int main() {
	
	
	std::string str = "123ooo456ooo789ooo147ooo258ooo369";
	std::string splitter = "ooo";
	String Sstr = str;

	Sstr.Split(splitter, [](const std::string &str, int idx) {
		std::cout << str << std::endl;
	});

	//LLD::String::Format
	//std::cout << Sstr;
	std::cin.get();
	return 0;
}