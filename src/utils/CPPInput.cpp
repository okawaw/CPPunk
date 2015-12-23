#include "CPPInput.h"

#include "ofConstants.h"

CPPKeys::id CPPInput::ms_lastKey = CPPKeys::NUM_KEYS;
bool CPPInput::ms_key[ CPPKeys::NUM_KEYS ];
std::set< CPPKeys::id > CPPInput::ms_press;
std::set< CPPKeys::id > CPPInput::ms_release;
unsigned int CPPInput::ms_keyNum = 0;

CPPKeys::id getKeyID( int key );

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

void CPPInput::onKeyDown( int key )
{
	const CPPKeys::id keyPressed = getKeyID( key );

	ms_lastKey = keyPressed;

	if ( !ms_key[ keyPressed ] )
	{
		ms_key[ keyPressed ] = true;
		++ms_keyNum;
		ms_press.insert( keyPressed );
	}
}

void CPPInput::onKeyUp( int key )
{
	const CPPKeys::id keyReleased = getKeyID( key );

	if ( ms_key[ keyReleased ] )
	{
		ms_key[ keyReleased ] = false;
		--ms_keyNum;
		ms_release.insert( keyReleased );
	}
}

CPPKeys::id getKeyID( int key )
{
	// Abstract away Glut and openFrameworks...
	switch ( key )
	{
		case OF_KEY_LEFT:
		{
			return CPPKeys::CPP_LEFT;
			break;
		}
		case OF_KEY_UP:
		{
			return CPPKeys::CPP_UP;
			break;
		}
		case OF_KEY_RIGHT:
		{
			return CPPKeys::CPP_RIGHT;
			break;
		}
		case OF_KEY_DOWN:
		{
			return CPPKeys::CPP_DOWN;
			break;
		}
		case OF_KEY_RETURN:
		{
			return CPPKeys::CPP_ENTER;
			break;
		}
		case ' ':
		{
			return CPPKeys::CPP_SPACE;
			break;
		}
		case OF_KEY_BACKSPACE:
		{
			return CPPKeys::CPP_BACKSPACE;
			break;
		}
		case OF_KEY_DEL:
		{
			return CPPKeys::CPP_DELETE;
			break;
		}
		case OF_KEY_END:
		{
			return CPPKeys::CPP_END;
			break;
		}
		case OF_KEY_ESC:
		{
			return CPPKeys::CPP_ESCAPE;
			break;
		}
		case OF_KEY_HOME:
		{
			return CPPKeys::CPP_HOME;
			break;
		}
		case OF_KEY_INSERT:
		{
			return CPPKeys::CPP_INSERT;
			break;
		}
		case '\t':
		{
			return CPPKeys::CPP_TAB;
			break;
		}
		case OF_KEY_PAGE_DOWN:
		{
			return CPPKeys::CPP_PAGE_DOWN;
			break;
		}
		case OF_KEY_PAGE_UP:
		{
			return CPPKeys::CPP_PAGE_UP;
			break;
		}
		case '[':
		case '{':
		{
			return CPPKeys::CPP_LEFT_SQUARE_BRACKET;
			break;
		}
		case ']':
		case '}':
		{
			return CPPKeys::CPP_RIGHT_SQUARE_BRACKET;
			break;
		}
		case 'a':
		case 'A':
		{
			return CPPKeys::CPP_A;
			break;
		}
		case 'b':
		case 'B':
		{
			return CPPKeys::CPP_B;
			break;
		}
		case 'c':
		case 'C':
		{
			return CPPKeys::CPP_C;
			break;
		}
		case 'd':
		case 'D':
		{
			return CPPKeys::CPP_D;
			break;
		}
		case 'e':
		case 'E':
		{
			return CPPKeys::CPP_E;
			break;
		}
		case 'f':
		case 'F':
		{
			return CPPKeys::CPP_F;
			break;
		}
		case 'g':
		case 'G':
		{
			return CPPKeys::CPP_G;
			break;
		}
		case 'h':
		case 'H':
		{
			return CPPKeys::CPP_H;
			break;
		}
		case 'i':
		case 'I':
		{
			return CPPKeys::CPP_I;
			break;
		}
		case 'j':
		case 'J':
		{
			return CPPKeys::CPP_J;
			break;
		}
		case 'k':
		case 'K':
		{
			return CPPKeys::CPP_K;
			break;
		}
		case 'l':
		case 'L':
		{
			return CPPKeys::CPP_L;
			break;
		}
		case 'm':
		case 'M':
		{
			return CPPKeys::CPP_M;
			break;
		}
		case 'n':
		case 'N':
		{
			return CPPKeys::CPP_N;
			break;
		}
		case 'o':
		case 'O':
		{
			return CPPKeys::CPP_O;
			break;
		}
		case 'p':
		case 'P':
		{
			return CPPKeys::CPP_P;
			break;
		}
		case 'q':
		case 'Q':
		{
			return CPPKeys::CPP_Q;
			break;
		}
		case 'r':
		case 'R':
		{
			return CPPKeys::CPP_R;
			break;
		}
		case 's':
		case 'S':
		{
			return CPPKeys::CPP_S;
			break;
		}
		case 't':
		case 'T':
		{
			return CPPKeys::CPP_T;
			break;
		}
		case 'u':
		case 'U':
		{
			return CPPKeys::CPP_U;
			break;
		}
		case 'v':
		case 'V':
		{
			return CPPKeys::CPP_V;
			break;
		}
		case 'w':
		case 'W':
		{
			return CPPKeys::CPP_W;
			break;
		}
		case 'x':
		case 'X':
		{
			return CPPKeys::CPP_X;
			break;
		}
		case 'y':
		case 'Y':
		{
			return CPPKeys::CPP_Y;
			break;
		}
		case 'z':
		case 'Z':
		{
			return CPPKeys::CPP_Z;
			break;
		}
		case OF_KEY_F1:
		{
			return CPPKeys::CPP_F1;
			break;
		}
		case OF_KEY_F2:
		{
			return CPPKeys::CPP_F2;
			break;
		}
		case OF_KEY_F3:
		{
			return CPPKeys::CPP_F3;
			break;
		}
		case OF_KEY_F4:
		{
			return CPPKeys::CPP_F4;
			break;
		}
		case OF_KEY_F5:
		{
			return CPPKeys::CPP_F5;
			break;
		}
		case OF_KEY_F6:
		{
			return CPPKeys::CPP_F6;
			break;
		}
		case OF_KEY_F7:
		{
			return CPPKeys::CPP_F7;
			break;
		}
		case OF_KEY_F8:
		{
			return CPPKeys::CPP_F8;
			break;
		}
		case OF_KEY_F9:
		{
			return CPPKeys::CPP_F9;
			break;
		}
		case OF_KEY_F10:
		{
			return CPPKeys::CPP_F10;
			break;
		}
		case OF_KEY_F11:
		{
			return CPPKeys::CPP_F11;
			break;
		}
		case OF_KEY_F12:
		{
			return CPPKeys::CPP_F12;
			break;
		}
		case '0':
		case ')':
		{
			return CPPKeys::CPP_DIGIT_0;
			break;
		}
		case '1':
		case '!':
		{
			return CPPKeys::CPP_DIGIT_1;
			break;
		}
		case '2':
		case '@':
		{
			return CPPKeys::CPP_DIGIT_2;
			break;
		}
		case '3':
		case '#':
		{
			return CPPKeys::CPP_DIGIT_3;
			break;
		}
		case '4':
		case '$':
		{
			return CPPKeys::CPP_DIGIT_4;
			break;
		}
		case '5':
		case '%':
		{
			return CPPKeys::CPP_DIGIT_5;
			break;
		}
		case '6':
		case '^':
		{
			return CPPKeys::CPP_DIGIT_6;
			break;
		}
		case '7':
		case '&':
		{
			return CPPKeys::CPP_DIGIT_7;
			break;
		}
		case '8':
		case '*':
		{
			return CPPKeys::CPP_DIGIT_8;
			break;
		}
		case '9':
		case '(':
		{
			return CPPKeys::CPP_DIGIT_9;
			break;
		}
		case '`':
		case '~':
		{
			return CPPKeys::CPP_GRAVE_ACCENT;
			break;
		}
		case '-':
		case '_':
		{
			return CPPKeys::CPP_MINUS;
			break;
		}
		case '=':
		case '+':
		{
			return CPPKeys::CPP_EQUALS;
			break;
		}
		case '\\':
		case '|':
		{
			return CPPKeys::CPP_BACKSLASH;
			break;
		}
		case ';':
		case ':':
		{
			return CPPKeys::CPP_SEMICOLON;
			break;
		}
		case '\'':
		case '"':
		{
			return CPPKeys::CPP_SINGLE_QUOTE;
			break;
		}
		case ',':
		case '<':
		{
			return CPPKeys::CPP_COMMA;
			break;
		}
		case '.':
		case '>':
		{
			return CPPKeys::CPP_PERIOD;
			break;
		}
		case '/':
		case '?':
		{
			return CPPKeys::CPP_SLASH;
			break;
		}
		default:
		{
			return CPPKeys::CPP_UNSPECIFIED;
			break;
		}
	}
}
