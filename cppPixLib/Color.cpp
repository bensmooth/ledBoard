#include "Color.h"

namespace Pix
{

	Color::Color()
		: m_r(0), m_g(0), m_b(0)
	{
	}

	Color::~Color()
	{
	}

	void Color::Write(std::ostream& outstream)
	{
		outstream.write((char*)&m_r, sizeof(uint8_t));
		outstream.write((char*)&m_g, sizeof(uint8_t));
		outstream.write((char*)&m_b, sizeof(uint8_t));
	}

	void Color::Read(std::istream& instream)
	{
		instream.read((char*)&m_r, sizeof(uint8_t));
		instream.read((char*)&m_g, sizeof(uint8_t));
		instream.read((char*)&m_b, sizeof(uint8_t));
	}

	void Color::Set(uint8_t r, uint8_t g, uint8_t b)
	{
		m_r = r;
		m_g = g;
		m_b = b;
	}

	uint8_t& Color::Red()
	{
		return m_r;
	}

	uint8_t& Color::Green()
	{
		return m_g;
	}

	uint8_t& Color::Blue()
	{
		return m_b;
	}

	const uint8_t& Color::Red() const
	{
		return m_r;
	}

	const uint8_t& Color::Green() const
	{
		return m_g;
	}

	const uint8_t& Color::Blue() const
	{
		return m_b;
	}
}
