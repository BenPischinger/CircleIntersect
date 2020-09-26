#include "PrimitivePainter.h"
#include <math.h>

// The primitive we use for rendering.
DWORD PrimitivePainter::ScreenVertex::FVF =  D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

void PrimitivePainter::MeasureScreen(  const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
{
	m_windowWidth = pBackBufferSurfaceDesc->Width;
	m_windowHeight = pBackBufferSurfaceDesc->Height;
}

// Draws a circle with the indicated radius and center onto the screen.
void  PrimitivePainter::PaintCircle(IDirect3DDevice9* pd3dDevice, const float centerPoint[], const float radius)
{
	const int numOfSegments = 100;
	const float angleDelta = 2.0f * D3DX_PI / numOfSegments;
	// Blue circle.
	const DWORD paintColor = D3DCOLOR_RGBA(0,0,255, 255);
	float x,y;
	
	for(int i = 0; i <= numOfSegments; ++i)
	{
		x = centerPoint[0] + radius * cosf(i * angleDelta);
		y = centerPoint[1] + radius * sinf(i * angleDelta);
		m_vertexBuffer[i].color = paintColor;
		m_vertexBuffer[i].z = 0.5f;
		m_vertexBuffer[i].h = 1.0f;
		m_vertexBuffer[i].x = x * m_windowWidth;
		m_vertexBuffer[i].y = y * m_windowHeight;
	}
	pd3dDevice->SetFVF( ScreenVertex::FVF );
	pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, numOfSegments, m_vertexBuffer, sizeof(ScreenVertex));
}


// Paints a line from a given starting point to the indicated direction.
// startPoint: One point on the line.
// direction: directional vector that points along the line.
void PrimitivePainter::PaintLine(IDirect3DDevice9* pd3dDevice, const float startPoint[], const float direction[])
{
	const float extensionFactor = 10.0f;
	float length = sqrtf(direction[0] * direction[0] + direction[1] * direction[1]);
	// greenish line circle.
	const DWORD paintColor = D3DCOLOR_RGBA(24,250,24, 255);
	m_vertexBuffer[0].color = paintColor;
	m_vertexBuffer[0].z = 0.5f;
	m_vertexBuffer[0].h = 1.0f;
	m_vertexBuffer[0].x = (startPoint[0] - extensionFactor * direction[0] / length) * m_windowWidth;
	m_vertexBuffer[0].y = (startPoint[1] - extensionFactor * direction[1] / length) * m_windowHeight;

	m_vertexBuffer[1] = m_vertexBuffer[0];
	m_vertexBuffer[1].x = (startPoint[0] + extensionFactor * direction[0] / length) * m_windowWidth;
	m_vertexBuffer[1].y = (startPoint[1] + extensionFactor * direction[1] / length) * m_windowHeight;

	pd3dDevice->SetFVF( ScreenVertex::FVF );
	pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, m_vertexBuffer, sizeof(ScreenVertex));
}


// Paints a small red cross at the indicated position.
// startPoint: Position where to paint the cross.
void PrimitivePainter::PaintCross(IDirect3DDevice9* pd3dDevice, const float startPoint[])
{
	const DWORD paintColor = D3DCOLOR_RGBA(255,0,0, 255);
	m_vertexBuffer[0].color = paintColor;
	m_vertexBuffer[0].z = 0.5f;
	m_vertexBuffer[0].h = 1.0f;
	m_vertexBuffer[0].x = startPoint[0]  * m_windowWidth - 10;
	m_vertexBuffer[0].y = startPoint[1]  * m_windowHeight + 10;
	m_vertexBuffer[1] = m_vertexBuffer[0];
	m_vertexBuffer[1].x = startPoint[0]  * m_windowWidth + 10;
	m_vertexBuffer[1].y = startPoint[1]  * m_windowHeight - 10;
	pd3dDevice->SetFVF( ScreenVertex::FVF );
	pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, m_vertexBuffer, sizeof(ScreenVertex));


	m_vertexBuffer[0].x = startPoint[0]  * m_windowWidth - 10;
	m_vertexBuffer[0].y = startPoint[1]  * m_windowHeight - 10;
	m_vertexBuffer[1].x = startPoint[0]  * m_windowWidth + 10;
	m_vertexBuffer[1].y = startPoint[1]  * m_windowHeight + 10;
	pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, m_vertexBuffer, sizeof(ScreenVertex));
	
}