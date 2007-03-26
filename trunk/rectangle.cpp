#include "rectangle.hpp"
#include "assert.hpp"
#include "debug.hpp"
#include <iostream>

Rectangle::Rectangle(const Rectangle &rect)
	: m_size(rect.m_size), m_position(rect.m_position),
	  m_ref(rect.m_ref)
{
	REQUIRE(
		(rect.getSize().x >= 0) &&
		(rect.getSize().y >= 0)
		);
	ENSURE(
		(this->getMin().x <= this->getMax().x) &&
		(this->getMin().y <= this->getMax().y)
		);
}

Rectangle::Rectangle(Pair size, Pair position, Pair reference)
	: m_size(size), m_position(position), m_ref(reference)
{
	// check why getting negative size rectangles sometime
	/*
	REQUIRE(
		(size.x >= 0) &&
		(size.y >= 0)
		);
	if (
		(size.x < 0) ||
		(size.y < 0)
		)
		debugPrint();
	
	ENSURE(
		(this->getMin().x <= this->getMax().x) &&
		(this->getMin().y <= this->getMax().y)
		);
	*/
}

Rectangle Rectangle::operator+(Pair distance) const
{
	return Rectangle(
		m_size,
		(m_position + distance),
		m_ref
	);
}

Rectangle Rectangle::operator-(Pair distance) const
{
	return Rectangle(
		m_size,
		(m_position - distance),
		m_ref
	);
}

bool Rectangle::intersect(const Rectangle &rect) const
{
	REQUIRE(
		(rect.getSize().x >= 0) &&
		(rect.getSize().y >= 0)
		);
	return (
		(getMin().x <= rect.getMax().x) &&
		(getMax().x >= rect.getMin().x) &&
		(getMin().y <= rect.getMax().y) &&
		(getMax().y >= rect.getMin().y) 
		);
}

void Rectangle::move(Pair distance)
{
	m_position += distance;
}

Pair Rectangle::getMin( void ) const
{
	return (m_position - m_ref);
}

Pair Rectangle::getMax( void ) const
{
	return (m_position - m_ref + m_size);
}

Pair Rectangle::getPos( void ) const
{
	return m_position;
}

Pair Rectangle::getSize( void ) const
{
	return m_size;
}

Pair Rectangle::getRef ( void ) const
{
	return m_ref;
}

void Rectangle::crop(const Rectangle &rect)
{
	REQUIRE(
		(rect.m_size.x >= 0) &&
		(rect.m_size.y >= 0)
		);

	m_position = m_position.min(rect.m_position);
	m_size = m_size.min(rect.m_position + rect.m_size - m_position);
	
	ENSURE(
		(this->getMin().x <= this->getMax().x) &&
		(this->getMin().y <= this->getMax().y)
		);
}

void Rectangle::setRect(const Pair& pos, const Pair& size)
{
	REQUIRE(
		(size.x >= 0) &&
		(size.y >= 0)
		);

	m_position.x = pos.x;
	m_position.y = pos.y;

	m_size.x = size.x;
	m_size.y = size.y;

	ENSURE(
		(this->getMin().x <= this->getMax().x) &&
		(this->getMin().y <= this->getMax().y)
		);
}

void Rectangle::setRect(const Rectangle& rect)
{
	REQUIRE(
		(rect.getSize().x >= 0) &&
		(rect.getSize().y >= 0)
		);

	m_position.x = rect.getSize().x;
	m_position.y = rect.getSize().y;

	m_size.x = rect.getPos().x;
	m_size.y = rect.getPos().y;

	ENSURE(
		(this->getMin().x <= this->getMax().x) &&
		(this->getMin().y <= this->getMax().y)
		);
}



/*
#include <iostream>

void Rectangle::debugPrint() const
{
	std::cout << "Rectangle: " << std::endl
		  << "\tSize:\t\t";
	m_size.debugPrint();
	std::cout << std::endl
		  << "\tPosition:\t";
	m_position.debugPrint();
	std::cout << std::endl
		  << "\tReference:\t";
	m_ref.debugPrint();
	std::cout << std::endl;
	
	std::cout << std::endl
		  << "\tMin:\t\t";
	m_min.debugPrint();
	std::cout << std::endl
		  << "\tMax:\t\t";
	m_max.debugPrint();
	std::cout << std::endl;
}

*/
