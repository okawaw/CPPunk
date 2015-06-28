#ifndef CPP_TILEMAP_H_
#define CPP_TILEMAP_H_

#include "CPPCanvas.h"

#include "ofImage.h"

#include "CPPBitmapData.h"

#include <string>

class CPPTilemap : public CPPCanvas
{
public:
	CPPTilemap( const CPPBitmapData& source,
	            unsigned int width,
	            unsigned int height,
	            unsigned int tileWidth,
	            unsigned int tileHeight,
	            bool autoCleanup = false );
	virtual ~CPPTilemap();

	unsigned int getTileWidth() const;
	unsigned int getTileHeight() const;
	unsigned int getColumns() const;
	unsigned int getRows() const;
	unsigned int getSetCount() const;
	bool isUsePositions() const;
	void setUsePositions( const bool usePositions );

	// Sets the index of the tile at the position.
	void setTile( unsigned int column, unsigned int row, unsigned int index = 0 );
	// Clears the tile at the position.
	void clearTile( unsigned int column, unsigned int row );
	// Gets the tile index at the position.
	unsigned int getTile( unsigned int column, unsigned int row ) const;
	// Sets a rectangular region of tiles to the index.
	void setRect( unsigned int column, unsigned int row,
	              unsigned int width = 1, unsigned int height = 1,
	              unsigned int index = 0 );
	// Makes a flood fill on the tilemap.
	void floodFill( unsigned int column, unsigned int row, unsigned int index = 0 );
	// Draws a line of tiles.
	void line( int x1, int y1, int x2, int y2, unsigned int index = 0 );
	// Draws an outline of a rectangle of tile.
	void setRectOutline( int x, int y, int width, int height, int id );
	// Updates the graphical cache for the whole tilemap.
	void updateAll();
	// Clears the rectangular region of tiles.
	void clearRect( unsigned int column, unsigned int row, unsigned int width = 1, unsigned int height = 1 );
	// Loads the tilemap tile index data from a string.
	void loadFromString( const std::string& str, char columnSep = ',', char rowSep = '\n' );
	// Saves the Tilemap tile index data to a string.
	void saveToString( std::string& ret, char columnSep = ',', char rowSep = '\n' );
	// Gets the 1D index of a tile from a 2D index (its column and row in the tileset image).
	unsigned int getIndex( unsigned int tilesColumn, unsigned int tilesRow );
	// Shifts all the tiles in the tilemap.
	void shiftTiles( int columns, int rows, bool wrap = false ); // TODO: implement
	// Get a subregion of the tilemap and return it as a new Tilemap.
	CPPTilemap* getSubMap ( int x, int y, int w, int h ); // TODO: implement?
	// Updates the graphical cache of a region of the tilemap.
	void updateRect( int x, int y, int width, int height, bool clear );
	// Used by shiftTiles to update a tile from the tilemap.
	void updateTile( unsigned int column, unsigned int row );
	// Create or initialise a Grid object from this tilemap.
	// void createGrid( solidTiles:Array, gridInput:* = null ) // TODO: implement


private:
	unsigned int* m_pTileMap;       // Map of tilemap indices.
	ofImage* m_pTileTexture;        // Texture data for the image. This is not owned/managed by this class. TODO: CONSTANT POINTER?
	CPPBitmapData m_tileSet;        // BitmapData for the image. This allows the resource manager to correctly handle the data.

	unsigned int m_tileWidth;
	unsigned int m_tileHeight;
	unsigned int m_columns;
	unsigned int m_rows;
	unsigned int m_setColumns;
	unsigned int m_setRows;
	unsigned int m_setCount;
	bool m_bUsePositions;

	void lineAlg( int x1, int y1, int x2, int y2, unsigned int index = 0 );

	CPPTilemap( const CPPTilemap& );
	CPPTilemap& operator=( const CPPTilemap& );
};

#endif
