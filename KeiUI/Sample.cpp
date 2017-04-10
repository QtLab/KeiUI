#include "Sample.h"

Sample::Sample(string name, HINSTANCE hInstance) : DXWindow(name, hInstance){

}

void Sample::render(){
	if(this->device){
		device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

		device->Present(0, 0, 0, 0);
	}
}