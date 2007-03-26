#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "pair.hpp"

// Inline Rectangle so can pass a real Rectangle to Image in order to
// save constructor call while having Image own a real Rectangle.  To
// do this, should probably basically just #include rectangle.cpp in
// class definition.

class Rectangle
{
  public:

	Rectangle( const Rectangle &rect );
	Rectangle(
		Pair size = Pair(),
		Pair position = Pair(),
		Pair reference = Pair()
		);
	

	// These don't move the Rectangle, they return a new one
	Rectangle operator+(Pair distance) const;
	Rectangle operator-(Pair distance) const;

	// intersect depends on getMin() being less than getMax()
	bool intersect(const Rectangle &rect) const;
	void move(Pair distance);
	void debugPrint() const;

	Pair getMin ( void ) const;
	Pair getMax ( void ) const;
	Pair getPos ( void ) const;
	Pair getSize( void ) const;
	Pair getRef ( void ) const;

	void crop(const Rectangle &rect); // restrict to inside of rect
	
	// Things to change the rectangle
	void setRect(const Pair& pos, const Pair& size);
	void setRect(const Rectangle& rect);

	// Other stuff
//	Rectangle asPartOf(const Rectangle &rect);
//	Rectangle getPartOf(const Rectangle &rect);
	
	// void print();
  private:
	Pair m_size, m_position, m_ref;
};



#endif // RECTANGLE_H
