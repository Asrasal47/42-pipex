		// unsigned int*  a1 = new unsigned int();

		try
		{
			Array<unsigned int>c = Array<unsigned int>(3);
			c[1] = 1;
			std::cout << c[1] << std::endl;
			std::cout << c[6] << std::endl;
			std::cout << c << std::endl;
			std::cout << c.size() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}


		std::cout << std::endl;
		std::cout << a << std::endl;
		std::cout << &a << std::endl;