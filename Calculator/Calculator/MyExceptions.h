#pragma once
#include <stdexcept>

namespace MyExceptions
{
	struct MathError : public std::runtime_error 
	{
		const char *error_msg;
		MathError(std::string _error_msg) : std::runtime_error(_error_msg) {}
		const char *what() const throw () 
		{
			return error_msg;
		}
	};

	struct SyntaxError : public std::runtime_error
	{
		const char  *error_msg;
		SyntaxError(std::string _error_msg) : std::runtime_error(_error_msg) {}
		const char *what() const throw ()
		{
			return error_msg;
		}
	};
}