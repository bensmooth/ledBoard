#pragma once
#include <cstdint>
#include <fstream>

namespace Pix
{
	class Color
	{
	public:
		Color();
		Color(uint8_t r, uint8_t g, uint8_t b);

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

		Color Inverted() const;

		friend bool operator==(const Color& lhs, const Color& rhs);

	private:
		uint8_t m_r;
		uint8_t m_g;
		uint8_t m_b;
	};

	inline bool operator==(const Color& lhs, const Color& rhs)
	{
		return (lhs.m_r == rhs.m_r && lhs.m_g == rhs.m_g && lhs.m_b == rhs.m_b);
	}

	inline bool operator!=(const Color& lhs, const Color& rhs)
	{
		return !operator==(lhs, rhs);
	}
}
