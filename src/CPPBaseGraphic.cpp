#include "CPPBaseGraphic.h"

CPPBaseGraphic::CPPBaseGraphic( bool autoCleanup/* = false */ ) :
  m_bActive( false )
, m_bVisible( true )
, m_posX( 0 )
, m_posY( 0 )
, m_bRelative( true )
, m_bAutoCleanup( autoCleanup )
{
}

CPPBaseGraphic::~CPPBaseGraphic()
{
}

bool CPPBaseGraphic::isActive() const { return m_bActive; }
void CPPBaseGraphic::setActive( const bool active ) { m_bActive = active; }

bool CPPBaseGraphic::isVisible() const { return m_bVisible; }
void CPPBaseGraphic::setVisible( const bool visible ) { m_bVisible = visible; }

float CPPBaseGraphic::getPosX() const { return m_posX; }
void CPPBaseGraphic::setPosX( const float x ) { m_posX = x; }

float CPPBaseGraphic::getPosY() const { return m_posY; }
void CPPBaseGraphic::setPosY( const float y ) { m_posY = y; }

bool CPPBaseGraphic::isRelative() const { return m_bRelative; }
void CPPBaseGraphic::setRelative( const bool relative ) { m_bRelative = relative; }

bool CPPBaseGraphic::isAutoCleanup() const { return m_bAutoCleanup; }

void CPPBaseGraphic::update()
{
}

void CPPBaseGraphic::draw( float x, float y )
{
}
