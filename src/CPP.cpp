#include "CPP.h"

#include "ofAppRunner.h"

static const int CAMERA_Z = 100;

static const std::string VERSION = "1.0.0";       // The CPPunk major version.

unsigned int CPP::m_width;                        // Width of the game.
unsigned int CPP::m_height;                       // Height of the game.
float CPP::m_halfWidth;                           // Half width of the game.
float CPP::m_halfHeight;                          // Half height of the game.

unsigned int CPP::m_frameRate;                    // Desired frame rate of the game.

StateHandler CPP::m_stateHandler;                 // Static state handler.

ofCamera CPP::m_camera;                           // Camera for the game.

CPP::CPP()
{
}

//--------------------------------------------------------------
void CPP::setup()
{
	// Set world camera to orthographic mode.
	m_camera.enableOrtho();
	// Move camera's top left position to (0, 0) by default.
	m_camera.setPosition( 0, m_height, CAMERA_Z );                            // IMPORTANT! Camera's y position must be sum of position and screen height.
	// Flip camera's y values to prevent mirroring.
	m_camera.setScale( 1, -1, 1 );
}

//--------------------------------------------------------------
void CPP::update()
{
	m_stateHandler.update();
}

//--------------------------------------------------------------
void CPP::draw()
{
	m_camera.begin();
	m_stateHandler.draw();
	m_camera.end();
}

//--------------------------------------------------------------
void CPP::keyPressed( int key )
{
	const Keys::id keyPressed = getKeyPressed( key );
	// Connect to Input Here.
	m_stateHandler.keyPressed( key );
}

//--------------------------------------------------------------
void CPP::keyReleased( int key )
{
	m_stateHandler.keyReleased( key );
}

//--------------------------------------------------------------
void CPP::mouseMoved( int x, int y )
{
	m_stateHandler.mouseMoved( x, y );
}

//--------------------------------------------------------------
void CPP::mouseDragged( int x, int y, int button )
{
	m_stateHandler.mouseDragged( x, y, button );
}

//--------------------------------------------------------------
void CPP::mousePressed( int x, int y, int button )
{
	m_stateHandler.mousePressed( x, y, button );
}

//--------------------------------------------------------------
void CPP::mouseReleased( int x, int y, int button )
{
	m_stateHandler.mouseReleased( x, y, button );
}

//--------------------------------------------------------------
void CPP::windowResized( int w, int h )
{
	// HACK: Somehow prevent resizing.
	ofSetWindowShape( m_width, m_height );

	m_stateHandler.windowResized( w, h );
}

//--------------------------------------------------------------
void CPP::gotMessage( ofMessage msg )
{
	m_stateHandler.gotMessage( msg );
}

//--------------------------------------------------------------
void CPP::dragEvent( ofDragInfo dragInfo )
{ 
	m_stateHandler.dragEvent( dragInfo );
}

void CPP::setWorld( BaseWorld* newWorld )
{
	m_stateHandler.changeWorld( newWorld );
}

unsigned int CPP::getWidth() { return m_width; }
unsigned int CPP::getHeight() { return m_height; }
float CPP::getHalfWidth() { return m_halfWidth; }
float CPP::getHalfHeight() { return m_halfHeight; }

void CPP::setWidth( unsigned int width )
{
	m_width = width;
	m_halfWidth = width / 2.0;
}

void CPP::setHeight( unsigned int height )
{
	m_height = height;
	m_halfHeight = height / 2.0;
}

void CPP::setFrameRate( unsigned int frameRate )
{
	m_frameRate = frameRate;
	ofSetFrameRate( frameRate );
}

float CPP::getCameraX()
{
	return m_camera.getPosition().x;
}

float CPP::getCameraY()
{
	return m_camera.getPosition().y - m_height;
}

void CPP::setCameraX( float x )
{
	m_camera.setPosition( x, m_camera.getPosition().y, CAMERA_Z );
}

void CPP::setCameraY( float y )
{
	m_camera.setPosition( m_camera.getPosition().x, y + m_height, CAMERA_Z );
}

void CPP::setCameraPos( float x, float y )
{
	m_camera.setPosition( x, y + m_height, CAMERA_Z );
}

// TODO: Write squareDistance
float CPP::distance( float x1, float y1, float x2, float y2 )
{
	return sqrt( ( x2 - x1 ) * ( x2 - x1 ) + ( y2 - y1 ) * ( y2 - y1 ) );
}

float CPP::distanceRects( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 )
{
	if ( x1 < x2 + w2 && x2 < x1 + w1 )
	{
		if ( y1 < y2 + h2 && y2 < y1 + h1 )
		{
			return 0;
		}
		if ( y1 > y2 )
		{
			return y1 - ( y2 + h2 );
		}
		return y2 - (y1 + h1);
	}
	if ( y1 < y2 + h2 && y2 < y1 + h1 )
	{
		if ( x1 > x2 )
		{
			return x1 - ( x2 + w2 );
		}
		return x2 - ( x1 + w1 );
	}
	if ( x1 > x2 )
	{
		if ( y1 > y2 )
		{
			return distance( x1, y1, ( x2 + w2 ), ( y2 + h2 ) );
		}
		return distance( x1, y1 + h1, x2 + w2, y2 );
	}
	if ( y1 > y2 )
	{
		return distance( x1 + w1, y1, x2, y2 + h2 );
	}
	return distance( x1 + w1, y1 + h1, x2, y2 );
}

float CPP::distanceRectPoint( float pX, float pY, float rX, float rY, float rW, float rH )
{
	if ( pX >= rX && pX <= rX + rW )
	{
		if ( pY >= rY && pY <= rY + rH )
		{
			return 0;
		}
		if ( pY > rY )
		{
			return pY - ( rY + rH );
		}
		return rY - pY;
	}
	if ( pY >= rY && pY <= rY + rH )
	{
		if ( pX > rX )
		{
			return pX - ( rX + rW );
		}
		return rX - pX;
	}
	if ( pX > rX )
	{
		if ( pY > rY )
		{
			return distance( pX, pY, rX + rW, rY + rH );
		}
		return distance( pX, pY, rX + rW, rY );
	}
	if ( pY > rY )
	{
		return distance( pX, pY, rX, rY + rH );
	}
	return distance( pX, pY, rX, rY );
}

Keys::id CPP::getKeyPressed( int key )
{
	// Abstract away Glut and openFrameworks...
	switch ( key )
	{
		case OF_KEY_LEFT:
		{
			return Keys::CPP_LEFT;
			break;
		}
		case OF_KEY_UP:
		{
			return Keys::CPP_UP;
			break;
		}
		case OF_KEY_RIGHT:
		{
			return Keys::CPP_RIGHT;
			break;
		}
		case OF_KEY_DOWN:
		{
			return Keys::CPP_DOWN;
			break;
		}
		case OF_KEY_RETURN:
		{
			return Keys::CPP_ENTER;
			break;
		}
		case ' ':
		{
			return Keys::CPP_SPACE;
			break;
		}
		case OF_KEY_BACKSPACE:
		{
			return Keys::CPP_BACKSPACE;
			break;
		}
		case OF_KEY_DEL:
		{
			return Keys::CPP_DELETE;
			break;
		}
		case OF_KEY_END:
		{
			return Keys::CPP_END;
			break;
		}
		case OF_KEY_ESC:
		{
			return Keys::CPP_ESCAPE;
			break;
		}
		case OF_KEY_HOME:
		{
			return Keys::CPP_HOME;
			break;
		}
		case OF_KEY_INSERT:
		{
			return Keys::CPP_INSERT;
			break;
		}
		case '\t':
		{
			return Keys::CPP_TAB;
			break;
		}
		case OF_KEY_PAGE_DOWN:
		{
			return Keys::CPP_PAGE_DOWN;
			break;
		}
		case OF_KEY_PAGE_UP:
		{
			return Keys::CPP_PAGE_UP;
			break;
		}
		case '[':
		case '{':
		{
			return Keys::CPP_LEFT_SQUARE_BRACKET;
			break;
		}
		case ']':
		case '}':
		{
			return Keys::CPP_RIGHT_SQUARE_BRACKET;
			break;
		}
		case 'a':
		case 'A':
		{
			return Keys::CPP_A;
			break;
		}
		case 'b':
		case 'B':
		{
			return Keys::CPP_B;
			break;
		}
		case 'c':
		case 'C':
		{
			return Keys::CPP_C;
			break;
		}
		case 'd':
		case 'D':
		{
			return Keys::CPP_D;
			break;
		}
		case 'e':
		case 'E':
		{
			return Keys::CPP_E;
			break;
		}
		case 'f':
		case 'F':
		{
			return Keys::CPP_F;
			break;
		}
		case 'g':
		case 'G':
		{
			return Keys::CPP_G;
			break;
		}
		case 'h':
		case 'H':
		{
			return Keys::CPP_H;
			break;
		}
		case 'i':
		case 'I':
		{
			return Keys::CPP_I;
			break;
		}
		case 'j':
		case 'J':
		{
			return Keys::CPP_J;
			break;
		}
		case 'k':
		case 'K':
		{
			return Keys::CPP_K;
			break;
		}
		case 'l':
		case 'L':
		{
			return Keys::CPP_L;
			break;
		}
		case 'm':
		case 'M':
		{
			return Keys::CPP_M;
			break;
		}
		case 'n':
		case 'N':
		{
			return Keys::CPP_N;
			break;
		}
		case 'o':
		case 'O':
		{
			return Keys::CPP_O;
			break;
		}
		case 'p':
		case 'P':
		{
			return Keys::CPP_P;
			break;
		}
		case 'q':
		case 'Q':
		{
			return Keys::CPP_Q;
			break;
		}
		case 'r':
		case 'R':
		{
			return Keys::CPP_R;
			break;
		}
		case 's':
		case 'S':
		{
			return Keys::CPP_S;
			break;
		}
		case 't':
		case 'T':
		{
			return Keys::CPP_T;
			break;
		}
		case 'u':
		case 'U':
		{
			return Keys::CPP_U;
			break;
		}
		case 'v':
		case 'V':
		{
			return Keys::CPP_V;
			break;
		}
		case 'w':
		case 'W':
		{
			return Keys::CPP_W;
			break;
		}
		case 'x':
		case 'X':
		{
			return Keys::CPP_X;
			break;
		}
		case 'y':
		case 'Y':
		{
			return Keys::CPP_Y;
			break;
		}
		case 'z':
		case 'Z':
		{
			return Keys::CPP_Z;
			break;
		}
		case OF_KEY_F1:
		{
			return Keys::CPP_F1;
			break;
		}
		case OF_KEY_F2:
		{
			return Keys::CPP_F2;
			break;
		}
		case OF_KEY_F3:
		{
			return Keys::CPP_F3;
			break;
		}
		case OF_KEY_F4:
		{
			return Keys::CPP_F4;
			break;
		}
		case OF_KEY_F5:
		{
			return Keys::CPP_F5;
			break;
		}
		case OF_KEY_F6:
		{
			return Keys::CPP_F6;
			break;
		}
		case OF_KEY_F7:
		{
			return Keys::CPP_F7;
			break;
		}
		case OF_KEY_F8:
		{
			return Keys::CPP_F8;
			break;
		}
		case OF_KEY_F9:
		{
			return Keys::CPP_F9;
			break;
		}
		case OF_KEY_F10:
		{
			return Keys::CPP_F10;
			break;
		}
		case OF_KEY_F11:
		{
			return Keys::CPP_F11;
			break;
		}
		case OF_KEY_F12:
		{
			return Keys::CPP_F12;
			break;
		}
		case '0':
		case ')':
		{
			return Keys::CPP_DIGIT_0;
			break;
		}
		case '1':
		case '!':
		{
			return Keys::CPP_DIGIT_1;
			break;
		}
		case '2':
		case '@':
		{
			return Keys::CPP_DIGIT_2;
			break;
		}
		case '3':
		case '#':
		{
			return Keys::CPP_DIGIT_3;
			break;
		}
		case '4':
		case '$':
		{
			return Keys::CPP_DIGIT_4;
			break;
		}
		case '5':
		case '%':
		{
			return Keys::CPP_DIGIT_5;
			break;
		}
		case '6':
		case '^':
		{
			return Keys::CPP_DIGIT_6;
			break;
		}
		case '7':
		case '&':
		{
			return Keys::CPP_DIGIT_7;
			break;
		}
		case '8':
		case '*':
		{
			return Keys::CPP_DIGIT_8;
			break;
		}
		case '9':
		case '(':
		{
			return Keys::CPP_DIGIT_9;
			break;
		}
		case '`':
		case '~':
		{
			return Keys::CPP_GRAVE_ACCENT;
			break;
		}
		case '-':
		case '_':
		{
			return Keys::CPP_MINUS;
			break;
		}
		case '=':
		case '+':
		{
			return Keys::CPP_EQUALS;
			break;
		}
		case '\\':
		case '|':
		{
			return Keys::CPP_BACKSLASH;
			break;
		}
		case ';':
		case ':':
		{
			return Keys::CPP_SEMICOLON;
			break;
		}
		case '\'':
		case '"':
		{
			return Keys::CPP_SINGLE_QUOTE;
			break;
		}
		case ',':
		case '<':
		{
			return Keys::CPP_COMMA;
			break;
		}
		case '.':
		case '>':
		{
			return Keys::CPP_PERIOD;
			break;
		}
		case '/':
		case '?':
		{
			return Keys::CPP_SLASH;
			break;
		}
		default:
		{
			return Keys::CPP_UNSPECIFIED;
			break;
		}
	}
}
