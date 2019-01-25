#include "TestNode.h"
#include <iostream>
int main()
{	
	std::cout << "Run Test for the Node<float>:" << std::endl;
	TestNode<float>::RunAllTest();
	std::cout << "\nRun Test for the Node<string>:" << std::endl;
	TestNode<std::string>::RunAllTest();
	std::cout << "\nRun Test for the Node<int>:" << std::endl;
	TestNode<int>::RunAllTest();

	return 0;
}
