#pragma once
#include <string>
#include <stdexcept>

namespace Pix
{
	class Exception : public std::runtime_error
	{
	public:
		explicit Exception(const std::string& what);
		explicit Exception(const char* what);

		virtual ~Exception() override;
	};
}
