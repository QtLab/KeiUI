#include "Direct2D1.h"
#include "Windows.h"

Direct2D1::Direct2D1() : factory(nullptr), target(nullptr), brush(nullptr) {

}

Direct2D1::~Direct2D1(){
	Utility::Release<ID2D1SolidColorBrush*>(this->brush);
	Utility::Release<ID2D1HwndRenderTarget*>(this->target);
	Utility::Release<ID2D1Factory*>(this->factory);
}

bool Direct2D1::init2D(string name){

	// create factory
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &(this->factory));
	if(FAILED(hr)){
		Windows::messageBox(this->hWnd, L"创建绘制引擎失败！", name, MB_ICONSTOP);
		return false;
	}

	// create target
	RECT rect;
	GetClientRect(this->hWnd, &rect);

	hr = this->factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(this->hWnd, D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top)),
		&(this->target)
	);

	if(FAILED(hr)){
		Windows::messageBox(this->hWnd, L"创建渲染对象失败！", name, MB_ICONSTOP);
		return false;
	}

	// create brush
	hr = this->target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &(this->brush));
	if(FAILED(hr)){
		Windows::messageBox(this->hWnd, L"创建绘制接口失败！", name, MB_ICONSTOP);
		return false;
	}

	return true;
}


void Direct2D1::drawRect(int x, int y, int witdh, int height){
	this->target->BeginDraw();
	this->target->Clear(D2D1::ColorF(D2D1::ColorF::White));

	this->target->DrawRectangle(D2D1::RectF(x, y, x + witdh, y + height), this->brush);

	this->target->EndDraw();
}
