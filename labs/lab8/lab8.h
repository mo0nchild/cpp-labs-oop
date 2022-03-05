#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace lab8 
{

	class IntegerException : public exception
	{
	public:
		enum error_types
		{
			DIVIDED_BY_ZERO = 120,
			CANNOT_CONVERTED = 250 // ... можно добавить
		};

		IntegerException(const char* message, string buffer, error_types status)
			: exception(message), error_state(buffer), status_code(status)
		{ }

		const char* get_error_state(void) const noexcept { return error_state.c_str(); }
		const char* what(void) const override { return exception::what(); }
		error_types get_status(void) const noexcept { return this->status_code; }

	private:
		string error_state;
		error_types status_code;
		
	};

	class IntegerStreamRead
	{
		istream* _stream;

	public: 
		explicit IntegerStreamRead(istream& stream)
			: _stream(&stream) { }

		int get_value(string message) const;
		
	};

	void lab(void);

}