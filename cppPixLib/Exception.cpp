#include "Exception.h"

namespace Pix
{
	Exception::Exception(const std::string& what)
		: runtime_error(what)
	{
	}

	Exception::Exception(const char* what)
		: runtime_error(what)
	{
	}

	Exception::~Exception()
	{
	}
}
