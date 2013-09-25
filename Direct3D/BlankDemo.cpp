#include "BlankDemo.h"


BlankDemo::BlankDemo(void)
{
}


BlankDemo::~BlankDemo(void)
{
}

bool BlankDemo::LoadContent()
{
	return true;
}

void BlankDemo::UnloadContent()
{

}


void BlankDemo::Update(float dt)
{

}

void BlankDemo::Render()
{
	if (_d3dDeviceContext == 0)
		return;

	float clearColor[4] = {0.0f,0.0f,0.25f,1.0f};
	_d3dDeviceContext->ClearRenderTargetView(_backBufferTarget,clearColor);

	_swapChain->Present(0,0);
}

