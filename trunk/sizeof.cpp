#include "sizeof.hpp"
#include <iostream>

//#include "Character.hpp"
//#include "abs.hpp"
#include "animating_sprite.hpp"
#include "animation.hpp"
#include "assert.hpp"
#include "ctimer.hpp"
#include "direction.hpp"
#include "extension.hpp"
#include "graphics.hpp"
#include "image.hpp"
#include "image_file.hpp"
#include "image_file_manager.hpp"
#include "image_manager.hpp"
#include "input.hpp"
//#include "inputpatterns.hpp"
//#include "logfile.hpp"  // not used
#include "pair.hpp"
#include "priority.hpp"
#include "rectangle.hpp"
//#include "sizeof.hpp"
#include "sprite.hpp"
//#include "testinput.hpp"
#include "timer.hpp"
#include "unit.hpp"

/*
#include "abs.cpp"
#include "animating_sprite.cpp"
#include "animation.cpp"
#include "assert.cpp"
#include "capsule.cpp"
#include "container.cpp"
#include "ctimer.cpp"
#include "graphics.cpp"
#include "image.cpp"
#include "image_file.cpp"
#include "image_file_manager.cpp"
#include "image_manager.cpp"
#include "input.cpp"
#include "inputpatterns.cpp"
#include "listelement.cpp"
#include "pair.cpp"
#include "priority.cpp"
#include "rectangle.cpp"
#include "sizeof.cpp"
#include "sprite.cpp"
#include "test.cpp"
#include "testinput.cpp"
#include "text.cpp"
#include "timer.cpp"
*/

void SizeOf::showSizes( void )
{
// Character.hpp
//std::cout << "Size of Move: " << sizeof( Move ) << std::endl;
//std::cout << "Size of IObject: " << sizeof( IObject ) << std::endl;
//std::cout << "Size of Character: " << sizeof( Character ) << std::endl;
//std::cout << "Size of Trigger: " << sizeof( Trigger ) << std::endl;

// abs.hpp

// animating_sprite.hpp
std::cout << "Size of AnimatingSprite: " << sizeof( AnimatingSprite ) << std::endl;
std::cout << "Size of AnimatingSpriteCompare: " << sizeof( AnimatingSpriteCompare ) << std::endl;

// animation.hpp
std::cout << "Size of Animation: " << sizeof( Animation ) << std::endl;

// assert.hpp

// ctimer.hpp
std::cout << "Size of CTime_Timer: " << sizeof( CTime_Timer ) << std::endl;

// direction.hpp

// extension.hpp

// graphics.hpp
std::cout << "Size of Graphics: " << sizeof( Graphics ) << std::endl;

// image.hpp
std::cout << "Size of Image: " << sizeof( Image ) << std::endl;

// image_file.hpp
std::cout << "Size of ImageFile: " << sizeof( ImageFile ) << std::endl;

// image_file_manager.hpp
std::cout << "Size of ImageFileManager: " << sizeof( ImageFileManager ) << std::endl;

// image_manager.hpp
std::cout << "Size of ImageManager: " << sizeof( ImageManager ) << std::endl;

// input.hpp
//std::cout << "Size of InputHandler: " << sizeof( InputHandler ) << std::endl;
//std::cout << "Size of Input: " << sizeof( Input ) << std::endl;

// inputpatterns.hpp
//std::cout << "Size of InputPatterns: " << sizeof( InputPatterns ) << std::endl;

// pair.hpp
std::cout << "Size of Pair: " << sizeof( Pair ) << std::endl;

// priority.hpp
std::cout << "Size of Priority: " << sizeof( Priority ) << std::endl;

// rectangle.hpp
std::cout << "Size of Rectangle: " << sizeof( Rectangle ) << std::endl;

// sizeof.hpp

// sprite.hpp
std::cout << "Size of Sprite: " << sizeof( Sprite ) << std::endl;
std::cout << "Size of SpriteCompare: " << sizeof( SpriteCompare ) << std::endl;

// testinput.hpp

// timer.hpp
std::cout << "Size of ITimer: " << sizeof( ITimer ) << std::endl;

// unit.hpp

}

