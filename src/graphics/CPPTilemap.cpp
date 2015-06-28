#include "CPPTilemap.h"

#include "../CPP.h"

#include <math.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <sstream>

struct TilemapData
{
	unsigned int arrayIndex;
	unsigned int column;
	unsigned int row;
};

CPPTilemap::CPPTilemap( const CPPBitmapData& source,
                        unsigned int width,
                        unsigned int height,
                        unsigned int tileWidth,
                        unsigned int tileHeight,
                        bool autoCleanup/* = false*/ ) :
  CPPCanvas( width, height, autoCleanup )
, m_pTileMap( NULL )
, m_pTileTexture( source.m_pTexture )
, m_tileSet( source )
, m_tileWidth( tileWidth )
, m_tileHeight( tileHeight )
, m_columns( m_width / tileWidth + ( m_width % tileWidth != 0 ) )
, m_rows( m_height / tileHeight + ( m_height % tileHeight != 0 ) )
, m_setColumns( m_pTileTexture->width / tileWidth + ( m_pTileTexture->width / tileWidth != 0 ) )
, m_setRows( m_pTileTexture->height / tileHeight + ( m_pTileTexture->height / tileHeight != 0 ) )
, m_setCount( m_setColumns * m_setRows )
, m_bUsePositions( false )
{
	m_pTileMap = new unsigned int[ m_columns * m_rows ];
}

CPPTilemap::~CPPTilemap()
{
	delete[] m_pTileMap;
}

void CPPTilemap::setTile( unsigned int column, unsigned int row, unsigned int index/* = 0*/ )
{
	if ( m_bUsePositions )
	{
		column /= m_tileWidth;
		row /= m_tileHeight;
	}
	index %= m_setCount;
	column %= m_columns;
	row %= m_rows;
	unsigned int tileX = (index % m_setColumns) * m_tileWidth;
	unsigned int tileY = (index / m_setColumns) * m_tileHeight;
	unsigned int pointX = column * m_tileWidth;
	unsigned int pointY = row * m_tileHeight;
	m_pTileMap[ column + ( row * m_columns ) ] = index;
	copyPixels( pointX, pointY, m_tileSet, false, true, tileX, tileY, m_tileWidth, m_tileHeight );
}

void CPPTilemap::clearTile( unsigned int column, unsigned int row )
{
	if ( m_bUsePositions )
	{
		column /= m_tileWidth;
		row /= m_tileHeight;
	}
	column %= m_columns;
	row %= m_rows;
	unsigned int tileX = column * m_tileWidth;
	unsigned int tileY = row * m_tileHeight;
	fill( tileX, tileY, m_tileWidth, m_tileHeight, 0, 0, 0, 0 );
}

unsigned int CPPTilemap::getTile( unsigned int column, unsigned int row ) const
{
	if ( m_bUsePositions )
	{
		column /= m_tileWidth;
		row /= m_tileHeight;
	}
	return m_pTileMap[ ( column % m_columns ) + ( ( row % m_rows ) * m_columns ) ];
}

void CPPTilemap::setRect( unsigned int column, unsigned int row,
              unsigned int width/* = 1*/, unsigned int height/* = 1*/,
              unsigned int index/* = 0*/ )
{
	if ( m_bUsePositions )
	{
		column /= m_tileWidth;
		row /= m_tileHeight;
		width /= m_tileWidth;
		height /= m_tileHeight;
	}
	column %= m_columns;
	row %= m_rows;
	unsigned int c = column;
	unsigned int r = column + width;
	unsigned int b = row + height;
	bool u = m_bUsePositions;
	m_bUsePositions = false;
	while ( row < b )
	{
		while ( column < r )
		{
			setTile( column, row, index );
			++column;
		}
		column = c;
		++row;
	}
	m_bUsePositions = u;
}

void CPPTilemap::floodFill( unsigned int column, unsigned int row, unsigned int index/* = 0*/ )
{
	if ( m_bUsePositions )
	{
		column /= m_tileWidth;
		row /= m_tileHeight;
	}
	column %= m_columns;
	row %= m_rows;

	std::queue<TilemapData> q;
	unsigned int target = m_pTileMap[ column + ( row * m_columns ) ];

	if ( target == index )
	{
		return;
	}

	TilemapData m;
	m.arrayIndex = column + ( row * m_columns );
	m.column = column;
	m.row = row;

	q.push( m );

	while ( !q.empty() )
	{
		m = q.front();

		// Set current item to index.
		m_pTileMap[ m.arrayIndex ] = index;

		// Check north and south for the target index.
		if (    m.row != 0
		     && m_pTileMap[ m.arrayIndex - m_columns ] == target )
		{
			TilemapData n = m;
			n.arrayIndex -= m_columns;
			--n.row;
			q.push( n );
		}
		if (    m.row + 1 != m_rows
		     && m_pTileMap[ m.arrayIndex + m_columns ] == target )
		{
			TilemapData s = m;
			s.arrayIndex += m_columns;
			++s.row;
			q.push( s );
		}

		// Check west for the target index.
		while (    m.column != 0
		        && m_pTileMap[ m.arrayIndex - 1 ] == target )
		{
			--m.arrayIndex;
			--m.column;

			// Set west item to index.
			m_pTileMap[ m.arrayIndex ] = index;

			// Check north and south for the target index.
			if (    m.row != 0
			     && m_pTileMap[ m.arrayIndex - m_columns ] == target )
			{
				TilemapData n = m;
				n.arrayIndex -= m_columns;
				--n.row;
				q.push( n );
			}
			if (    m.row + 1 != m_rows
			     && m_pTileMap[ m.arrayIndex + m_columns ] == target )
			{
				TilemapData s = m;
				s.arrayIndex += m_columns;
				++s.row;
				q.push( s );
			}
		}
		m = q.front();
		// Check east for the target index.
		while (    m.column + 1 != m_columns
		        && m_pTileMap[ m.arrayIndex + 1 ] == target )
		{
			++m.arrayIndex;
			++m.column;

			// Set east item to index.
			m_pTileMap[ m.arrayIndex ] = index;

			// Check north and south for the target index.
			if (    m.row != 0
			     && m_pTileMap[ m.arrayIndex - m_columns ] == target )
			{
				TilemapData n = m;
				n.arrayIndex -= m_columns;
				--n.row;
				q.push( n );
			}
			if (    m.row + 1 != m_rows
			     && m_pTileMap[ m.arrayIndex + m_columns ] == target )
			{
				TilemapData s = m;
				s.arrayIndex += m_columns;
				++s.row;
				q.push( s );
			}
		}
		q.pop();
	}
	updateAll();
}

void CPPTilemap::line( int x1, int y1, int x2, int y2, unsigned int index/* = 0*/ )
{
	if ( m_bUsePositions )
	{
		x1 /= m_tileWidth;
		y1 /= m_tileHeight;
		x2 /= m_tileWidth;
		y2 /= m_tileHeight;
	}
	x1 %= m_columns;
	y1 %= m_rows;
	x2 %= m_columns;
	y2 %= m_rows;

	lineAlg( x1, y1, x2, y2, index );
	updateAll();
}

void CPPTilemap::setRectOutline( int x, int y, int width, int height, int id )
{
	if ( m_bUsePositions )
	{
		x /= m_tileWidth;
		y /= m_tileHeight;
		width /= m_tileWidth;
		height /= m_tileHeight;
	}
	x %= m_columns;
	y %= m_rows;

	lineAlg( x, y, x + width, y, id );
	lineAlg( x, y + height, x + width, y + height, id );
	lineAlg( x, y, x, y + height, id );
	lineAlg( x + width, y, x + width, y + height, id );
	updateAll();
}

void CPPTilemap::updateAll()
{
	updateRect( 0, 0, m_columns, m_rows, false );
}

void CPPTilemap::clearRect( unsigned int column, unsigned int row, unsigned int width/* = 1*/, unsigned int height/* = 1*/ )
{
	if ( m_bUsePositions )
	{
		column /= m_tileWidth;
		row /= m_tileHeight;
		width /= m_tileWidth;
		height /= m_tileHeight;
	}
	column %= m_columns;
	row %= m_rows;

	unsigned int c = column;
	unsigned int r = column + width;
	unsigned int b = row + height;
	bool u = m_bUsePositions;
	m_bUsePositions = false;

	while ( row < b )
	{
		while ( column < r )
		{
			clearTile( column, row );
			++column;
		}
		column = c;
		++row;
	}
	m_bUsePositions = u;
}

void CPPTilemap::loadFromString( const std::string& str, char columnSep/* = ','*/, char rowSep/* = '\n'*/ )
{
	bool u = m_bUsePositions;
	m_bUsePositions = false;
	std::vector< std::string > row;
	CPPUtil::split( str, rowSep, row );
	int rows = row.size();
	std::vector< std::string > col;
	int cols;
	int x;
	int y;

	for ( y = 0; y < rows; ++y )
	{
		if ( row[ y ] == "" )
		{
			continue;
		}
		col.clear();
		CPPUtil::split( row[ y ], columnSep, col );
		cols = col.size();

		for ( x = 0; x < cols; ++x )
		{
			if ( col[ x ] == "" )
			{
				continue;
			}
			setTile( x, y, strtoul( col[ x ].c_str(), NULL, 10 ) );
		}
	}
	m_bUsePositions = u;
}

void CPPTilemap::saveToString( std::string& ret, char columnSep/* = ','*/, char rowSep/* = '\n'*/ )
{
	std::stringstream ss;
	unsigned int x;
	unsigned int y;

	for ( y = 0; y < m_rows; ++y )
	{
		for ( x = 0; x < m_columns; ++x )
		{
			ss << m_pTileMap[ x + ( y * m_columns ) ];
			if ( x + 1 != m_columns )
			{
				ss << columnSep;
			}
		}
		if ( y + 1 != m_rows )
		{
			ss << rowSep;
		}
	}
	ret = ss.str();
}

unsigned int CPPTilemap::getIndex( unsigned int tilesColumn, unsigned int tilesRow )
{
	if ( m_bUsePositions )
	{
		tilesColumn /= m_tileWidth;
		tilesRow /= m_tileHeight;
	}

	return ( tilesRow % m_setRows ) * m_setColumns + ( tilesColumn % m_setColumns );
}

void CPPTilemap::shiftTiles( int columns, int rows, bool wrap/* = false*/ )
{
	/*
	if ( m_bUsePositions )
	{
		columns /= m_tileWidth;
		rows /= m_tileHeight;
	}

	if ( wrap )
	{

	}

	if ( columns != 0 )
	{
		shift( columns * m_tileWidth, 0 );
		if ( wrap )
		{

		}
	}
	*/
}

CPPTilemap* CPPTilemap::getSubMap ( int x, int y, int w, int h )
{
	CPPTilemap* ret = NULL;
	return ret;
}

void CPPTilemap::updateRect( int x, int y, int width, int height, bool clear )
{
	int _x = x;
	int _y = y;
	width += x;
	height += y;
	bool u = m_bUsePositions;
	m_bUsePositions = false;
	if ( clear )
	{
		while ( _y < height )
		{
			while ( _x < width )
			{
				clearTile( _x++, _y );
			}
			_x = x;
			++_y;
		}
	}
	else
	{
		while ( _y < height )
		{
			while ( _x < width )
			{
				updateTile( _x++, _y );
			}
			_x = x;
			++_y;
		}
	}
	m_bUsePositions = u;
}

void CPPTilemap::updateTile( unsigned int column, unsigned int row )
{
	setTile( column, row, m_pTileMap[ ( column % m_columns ) + ( ( row % m_rows ) * m_columns ) ] );
}

void CPPTilemap::lineAlg( int x1, int y1, int x2, int y2, unsigned int index/* = 0*/ )
{
	int deltaX = x2 - x1;
	const char iX = ( deltaX > 0 ) - ( deltaX < 0 );
	deltaX = abs( deltaX ) << 1;

	int deltaY = y2 - y1;
	const char iY = ( deltaY > 0 ) - ( deltaY < 0 );
	deltaY = abs( deltaY ) << 1;

	m_pTileMap[ x1 + ( y1 * m_columns ) ] = index;

	if ( deltaX >= deltaY )
	{
		int error = deltaY - ( deltaX >> 1 );

		while ( x1 != x2 )
		{
			if ( ( error >= 0 ) && ( error || ( iX > 0 ) ) )
			{
				error -= deltaX;
				y1 += iY;
			}
			// Else, do nothing.
			error += deltaY;
			x1 += iX;

			m_pTileMap[ x1 + ( y1 * m_columns ) ] = index;
		}
	}
	else
	{
		int error = deltaX - ( deltaY >> 1 );

		while ( y1 != y2 )
		{
			if ( ( error >= 0 ) && ( error || ( iY > 0 ) ) )
			{
				error -= deltaY;
				x1 += iX;
			}
			// Else, do nothing.
			error += deltaX;
			y1 += iY;

			m_pTileMap[ x1 + ( y1 * m_columns ) ] = index;
		}
	}
}
