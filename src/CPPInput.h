#ifndef CPP_INPUT_H_
#define CPP_INPUT_H_

#include "CPPKey.h"

#include <set>

class CPPInput
{
public:
	static CPPKeys::id getlastKey();

	// If the key is held down.
	static bool check( CPPKeys::id key );

	// If the key was pressed this frame.
	static bool pressed( CPPKeys::id key );

	// If the key was released this frame.
	static bool released( CPPKeys::id key );

	// Called by CPP's update to update the input.
	static void update();

	// Clears all input states.
	static void clear();

	// Event handler called by CPP's event handler.
	static void onKeyDown( CPPKeys::id key );

	// Event handler called by CPP's event handler.
	static void onKeyUp( CPPKeys::id key );


private:
	static CPPKeys::id ms_lastKey;              // The last key pressed.
	static bool ms_key[ CPPKeys::NUM_KEYS ];    // An array of keys' states.
	static std::set< CPPKeys::id > ms_press;    // A set of all keys pressed in this frame.
	static std::set< CPPKeys::id > ms_release;  // A set of all keys released in this frame.
	static unsigned int ms_keyNum;              // The number of currently pressed keys.
};

#endif
