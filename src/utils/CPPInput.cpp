#include "CPPInput.h"

CPPKeys::id CPPInput::ms_lastKey = CPPKeys::NUM_KEYS;
bool CPPInput::ms_key[ CPPKeys::NUM_KEYS ];
std::set< CPPKeys::id > CPPInput::ms_press;
std::set< CPPKeys::id > CPPInput::ms_release;
unsigned int CPPInput::ms_keyNum = 0;

CPPKeys::id CPPInput::getlastKey() { return ms_lastKey; }

bool CPPInput::check( CPPKeys::id key )
{
	return ( key < 0 ) ? ( ms_keyNum > 0 ) : ( ms_key[ key ] );
}

bool CPPInput::pressed( CPPKeys::id key )
{
	return ( key < 0 ) ? ( !ms_press.empty() ) : ( ms_press.find( key ) != ms_press.end() );
}

bool CPPInput::released( CPPKeys::id key )
{
	return ( key < 0 ) ? ( !ms_release.empty() ) : ( ms_release.find( key ) != ms_release.end() );
}

void CPPInput::update()
{
	ms_press.clear();
	ms_release.clear();
}

void CPPInput::clear()
{
	ms_press.clear();
	ms_release.clear();

	for ( unsigned int i = 0; i < CPPKeys::NUM_KEYS; ++i )
	{
		ms_key[ i ] = false;
	}

	ms_lastKey = CPPKeys::NUM_KEYS;

	ms_keyNum = 0;
}

void CPPInput::onKeyDown( CPPKeys::id key )
{
	ms_lastKey = key;

	if ( !ms_key[ key] )
	{
		ms_key[ key ] = true;
		++ms_keyNum;
		ms_press.insert( key );
	}
}

void CPPInput::onKeyUp( CPPKeys::id key )
{
	if ( ms_key[ key] )
	{
		ms_key[ key ] = false;
		--ms_keyNum;
		ms_release.insert( key );
	}
}
