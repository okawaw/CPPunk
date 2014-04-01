#include "CPP.h"

#include "ofAppRunner.h"

static const int CAMERA_Z = 100;

static const std::string VERSION = "1.0.0";       // The CPPunk major version.

unsigned int CPP::m_width;                        // Width of the game.
unsigned int CPP::m_height;                       // Height of the game.
float CPP::m_halfWidth;                           // Half width of the game.
float CPP::m_halfHeight;                          // Half height of the game.

unsigned int CPP::m_frameRate;                    // Desired frame rate of the game.

CPPStateHandler CPP::m_stateHandler;                 // Static state handler.

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
	const CPPKeys::id keyPressed = getKeyPressed( key );
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

void CPP::setWorld( CPPBaseWorld* newWorld )
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

CPPKeys::id CPP::getKeyPressed( int key )
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
