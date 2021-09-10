#include "AppFramework/Application.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
	VulkanEngineApplication::Application application{};

	try 
	{
		application.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}