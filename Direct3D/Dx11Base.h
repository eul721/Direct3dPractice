#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <DxErr.h>

class Dx11Base
{
public:
	Dx11Base(void);
	virtual ~Dx11Base(void);

	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void Shutdown();

	virtual bool LoadContent();
	virtual void UnloadContent();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
protected:
	HINSTANCE _hInstance;
	HWND _hwnd;

	D3D_DRIVER_TYPE _driverType;
	D3D_FEATURE_LEVEL _featureLevel;

	ID3D11Device* _d3dDevice;
	ID3D11DeviceContext* _d3dDeviceContext;
	IDXGISwapChain* _swapChain;
	ID3D11RenderTargetView* _backBufferTarget;

	struct VertexPos{
		XMFLOAT3 pos;
	};


};

