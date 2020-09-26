#pragma once

#include "DXUT/DXUT.h"
#include "DXUT/DXUTmisc.h"

// This is a helper class that takes care of painting all the primitives 
// for the circle demonstration. The coordinates it processes are in the 
// [0,1] Range and get automatically scaled to the required window size.
class PrimitivePainter
{
public:

	// Measures the screen.
	void MeasureScreen( const D3DSURFACE_DESC* pBackBufferSurfaceDesc);

	// Draws a circle with the indicated radius and center onto the screen.
	void PaintCircle(IDirect3DDevice9* pd3dDevice, const float centerPoint[], const float radius);

	// Paints a line from a given starting point to the indicated direction.
	void PaintLine(IDirect3DDevice9* pd3dDevice, const float startPoint[], const float direction[]);

	// Paints a small red cross at the indicated position.
	void PaintCross(IDirect3DDevice9* pd3dDevice, const float startPoint[]);


private:
	
	// The width of the window in pixel.
	int m_windowWidth;
	// The height of the window in pixel.
	int m_windowHeight;

	// We need a position and a color to draw the line.
	struct ScreenVertex
	{
		float x, y, z, h;
		D3DCOLOR color;

		static DWORD FVF;
	};
	
	

	// We hardcode the vertex array here.
	enum { MAX_NUM_OF_VERTICES = 512};
	
	// A predetermined array with the vertices we can store.
	ScreenVertex m_vertexBuffer[MAX_NUM_OF_VERTICES];


};

