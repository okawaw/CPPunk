#ifndef CPP_BASE_GRAPHIC_H_
#define CPP_BASE_GRAPHIC_H_

class CPPBaseGraphic
{
public:
	CPPBaseGraphic();
	virtual ~CPPBaseGraphic();

	virtual void update();
	virtual void draw( float x, float y );

	bool isActive() const;
	void setActive( const bool active );

	bool isVisible() const;
	void setVisible( const bool visible );

	float getPosX() const;
	void setPosX( const float x );

	float getPosY() const;
	void setPosY( const float y );

	bool isRelative() const;
	void setRelative( const bool relative );

protected:
	bool m_bActive;               // If the graphic should update.
	bool m_bVisible;              // If the graphic should update.

	float m_posX;                 // X offset.
	float m_posY;                 // Y offset.

	bool m_bRelative;             // If the graphic should render at its position relative to its parent Entity's position.

};

#endif
