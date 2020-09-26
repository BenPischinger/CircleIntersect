// -------------------------------------------------------------------------------------
// This is the main file for the circle test application
// -------------------------------------------------------------------------------------

#include "DXUT/DXUT.h"
#include "DXUT/DXUTmisc.h"
#include "resource.h"
#include "PrimitivePainter.h"
#include "IntersectionCalculator.h"
#include <math.h>

// --------------------------------------------------------------------------------------
// The for the geometric information.
// --------------------------------------------------------------------------------------
const float g_circleCenter[2] = {0.75f, 0.5f};
const float g_circleRadius = 0.23f;
float g_linePosition[2] = {0.25f, 0.5f};
float g_lineAngle = 0.0f;
float g_lineDirection[2] = {1.0f, 0.0f};


// The calculator for the magic.
IntersectionCalculator g_calculator(g_circleCenter, g_circleRadius);
// The unit we use for primitive painting.
PrimitivePainter g_painter;

// --------------------------------------------------------------------------------------
// Keyboard State
// --------------------------------------------------------------------------------------

// Indicates that the up cursor was pressed.
bool g_wasUp = false;
// Indicates that the down cursor was pressed.
bool g_wasDown = false;
// Was the w key pressed.
bool g_wasW = false;
// Was the s key pressed.
bool g_wasS = false;


//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable(  D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );

void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext );


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    // Set DXUT callbacks
	DXUTSetCallbackD3D9DeviceReset(OnD3D9ResetDevice);
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackKeyboard( OnKeyboard );
    DXUTSetCallbackFrameMove( OnFrameMove );

    DXUTInit( true, true, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"Circle Test" );
    DXUTCreateDevice( true, 640, 640 );
    DXUTMainLoop(); // Enter into the DXUT render loop

    return DXUTGetExitCode();
}

// Handle the window size change.
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr = S_OK;
	pd3dDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, false);
	g_painter.MeasureScreen(pBackBufferSurfaceDesc);
 
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext  )
{
    //
    // Clear the back buffer to black
    //
    pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,  D3DCOLOR_RGBA(0,0,0, 255), 0.0f, 0);
	pd3dDevice->BeginScene();
	g_painter.PaintCircle(pd3dDevice, g_circleCenter, g_circleRadius);
	g_painter.PaintLine(pd3dDevice, g_linePosition, g_lineDirection);
	float position[2];
	int targets = g_calculator.GetAmountOfIntersectionPoints();
	for(int i = 0; i < targets; ++i)
	{
		g_calculator.GetIntersectionPoint(i, position);
		g_painter.PaintCross(pd3dDevice, position);

	}
	pd3dDevice->EndScene();
}




//--------------------------------------------------------------------------------------
// Update the scene here.
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	if (g_wasUp)
		g_lineAngle -= fElapsedTime;
	if (g_wasDown)
		g_lineAngle += fElapsedTime;

	g_lineDirection[0] = cosf(g_lineAngle);
	g_lineDirection[1] = sinf(g_lineAngle);

	if (g_wasS)
		g_linePosition[1] += 0.25f * fElapsedTime;
	if (g_wasW)
		g_linePosition[1] -= 0.25f * fElapsedTime;

	g_calculator.ComputeIntersectionWithLine(g_linePosition, g_lineDirection);
}





//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{

	if (nChar == VK_UP)
	{
		g_wasUp = bKeyDown;
	}
	if (nChar == VK_DOWN)
	{
		g_wasDown = bKeyDown;
	}
	if (nChar == 'W')
	{
		g_wasW = bKeyDown;
	}
	if (nChar == 'S')
	{
		g_wasS = bKeyDown;
	}
}



