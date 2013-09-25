#include "Dx11Base.h"


Dx11Base::Dx11Base(void) : _driverType(D3D_DRIVER_TYPE_NULL),
	_featureLevel(D3D_FEATURE_LEVEL_11_0),_d3dDevice(0),_d3dDeviceContext(0),
	_swapChain(0),_backBufferTarget(0)
{

}


Dx11Base::~Dx11Base(void)
{
	Shutdown();
}

bool Dx11Base::LoadContent()
{
	//Override with demo specifics
	return true;
}

void Dx11Base::UnloadContent()
{
	//Override with demo specifics
}

void Dx11Base::Shutdown()
{
	UnloadContent();

	if(_backBufferTarget) _backBufferTarget->Release();
	if(_swapChain) _swapChain->Release();
	if(_d3dDeviceContext) _d3dDeviceContext->Release();
	if(_d3dDevice) _d3dDevice->Release();
	_d3dDevice = 0;
	_d3dDeviceContext = 0;
	_swapChain = 0;
	_backBufferTarget = 0;
}

bool Dx11Base::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	_hInstance = hInstance;
	_hwnd = hwnd;

	RECT dimensions;
	GetClientRect(hwnd,&dimensions);

	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};
	 
	unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc,sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	unsigned int driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver){
		result = D3D11CreateDeviceAndSwapChain(0,driverTypes[driver],0,
			creationFlags,featureLevels,totalFeatureLevels,D3D11_SDK_VERSION,&swapChainDesc,
			&_swapChain,&_d3dDevice,&_featureLevel,&_d3dDeviceContext);

		if (SUCCEEDED(result))
		{
			_driverType = driverTypes[driver];
			break;
		}
	}
	if (FAILED(result)){
		DXTRACE_MSG("Failed to create the Direct3D device!");
		return false;
	}
	ID3D11Texture2D* backBufferTexture;
	result = _swapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),
		(LPVOID*)&backBufferTexture);

	if (FAILED(result)){
		DXTRACE_MSG("Failed to get the swap chain back buffer!");
		return false;
	}

	result = _d3dDevice->CreateRenderTargetView(backBufferTexture,0,&_backBufferTarget);

	if(backBufferTexture)
		backBufferTexture->Release();

	if(FAILED(result)){
		DXTRACE_MSG("Failed to create the render target view!");
		return false;
	}

	_d3dDeviceContext->OMSetRenderTargets(1,&_backBufferTarget,0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	_d3dDeviceContext->RSSetViewports(1,&viewport);

	return LoadContent();


}

