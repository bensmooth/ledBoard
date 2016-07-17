#pragma once
#include <cstdint>
#include <fstream>

namespace Pix
{

	class Color
	{
	public:
		Color();
		~Color();

		void Write(std::ostream& outstream);
		void Read(std::istream& instream);

		void Set(uint8_t r, uint8_t g, uint8_t b);

		uint8_t& Red();
		uint8_t& Green();
		uint8_t& Blue();

		const uint8_t& Red() const;
		const uint8_t& Green() const;
		const uint8_t& Blue() const;

	private:
		uint8_t m_r;
		uint8_t m_g;
		uint8_t m_b;
	};
}
