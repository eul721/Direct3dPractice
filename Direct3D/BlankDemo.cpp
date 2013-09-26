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

	VertexPos vertices[] = 
	{
		XMFLOAT3(0.5f,0.5f,0.5f),
		XMFLOAT3(0.5f,-0.5f,0.5f),
		XMFLOAT3(-0.5f,-0.5f,0.5f)
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc,sizeof(vertexDesc));
	
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos)*3;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData,sizeof(resourceData));
	resourceData.pSysMem = vertices;

	ID3D11Buffer* vertexBuffer;
	HRESULT result = _d3dDevice->CreateBuffer(&vertexDesc,&resourceData,&vertexBuffer);


	float clearColor[4] = {0.0f,0.0f,0.25f,1.0f};
	_d3dDeviceContext->ClearRenderTargetView(_backBufferTarget,clearColor);

	_swapChain->Present(0,0);
}

