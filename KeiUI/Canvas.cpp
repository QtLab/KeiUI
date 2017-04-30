#include "Canvas.h"
#include "Window.h"

namespace KeiUI{
	Canvas::Canvas(IDirect3DDevice9* device, ID3DXSprite* sprite)
		: device(device), sprite(sprite), tmpTexture(nullptr), textureList(Array<string, TextureInfo>()) 
	{

	}

	Canvas::~Canvas(){
		for(int i = 0; i < this->textureList.size(); i++){
			Utility::Release(this->textureList.last().texture);
			this->textureList.remove();
		}

		this->tmpTexture = nullptr;
	}

	BYTE* Canvas::getPixel(string name, int* pitch){
		D3DLOCKED_RECT lockedRect;

		TextureInfo info = this->textureList.get(name);
		this->tmpTexture = info.texture;

		if(tmpTexture != nullptr){
			this->tmpTexture->LockRect(0, &lockedRect, nullptr, 0);

			*pitch = lockedRect.Pitch;
			BYTE* pixels= (BYTE*)lockedRect.pBits;

			this->tmpTexture->UnlockRect(0);
			return pixels;
		}

		return nullptr;
	}

	void Canvas::drawRect(Rect rect, float depth, float rotation){

		if(rect.getTexture() != L""){
			D3DXIMAGE_INFO tmp;
			this->loadTexture(rect.getTexture(), &tmp);

		}else{
			string name = rect.toString();

			this->nullTexture(name, rect.getWidth(), rect.getHeight());
		}

		D3DXMATRIX positionMatrix, scaleMatrix, rotateMatrix, finalMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, rotation);
		D3DXMatrixScaling(&scaleMatrix, rect.getScale(), rect.getScale(), 0.0f);
		D3DXMatrixTranslation(&positionMatrix, rect.getX(), rect.getY(), depth);

		finalMatrix = scaleMatrix * rotateMatrix * positionMatrix;
		this->sprite->SetTransform(&finalMatrix);

		this->sprite->Draw(this->tmpTexture, nullptr, nullptr, nullptr, rect.getColor().toD3DCOLOR());
	}

	void Canvas::nullTexture(string name, int width, int height){

		if(!(this->textureList.exist(name))){

			this->tmpTexture = nullptr;
			HRESULT hr = D3DXCreateTexture(this->device, width, height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(this->tmpTexture));

			if(SUCCEEDED(hr)){

				D3DLOCKED_RECT lockedRect;
				this->tmpTexture->LockRect(0, &lockedRect, nullptr, 0);

				BYTE* pixels= (BYTE*)lockedRect.pBits;
				for(int i = 0; i < height; i++){
					for(int j = 0; j < width; j++){
						int index = i * 4 + j * lockedRect.Pitch;
						pixels[index] = 255;
						pixels[index + 1] = 255;
						pixels[index + 2] = 255;
						pixels[index + 3] = 255;
					}
				}

				this->tmpTexture->UnlockRect(0);

				// 记录资源
				D3DXIMAGE_INFO info;
				info.Width = width;
				info.Height = height;

				this->textureList.add(name, TextureInfo(this->tmpTexture, info));
			}

		}else{

			TextureInfo tmp = this->textureList.get(name);
			this->tmpTexture = tmp.texture;
		}

	}

	void Canvas::loadTexture(string source, D3DXIMAGE_INFO* info){

		if(!(this->textureList.exist(source))){
			// 打开文件
			HANDLE file = CreateFile(
				source.c_str(), GENERIC_READ, 0, NULL,
				OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL
			);

			if (file == INVALID_HANDLE_VALUE){
				return;
			}

			// 获取文件的大小
			DWORD imageSize = GetFileSize(file, nullptr);
			BYTE* imageBuff = new BYTE[imageSize];
			if (!imageBuff) {
				CloseHandle(file);
				return;
			}

			// 读入文件数据
			DWORD buffSize;
			ReadFile(file, imageBuff, imageSize, &buffSize, nullptr);
			CloseHandle(file);

			// 数据解密

			// 获取图片的大小
			D3DXIMAGE_INFO* tmpInfo = nullptr;
			if(info != nullptr){
				tmpInfo = info;
			}else{
				tmpInfo = new D3DXIMAGE_INFO();
			}

			if (FAILED(D3DXGetImageInfoFromFileInMemory(imageBuff, buffSize, tmpInfo))) {
				Utility::Delete(imageBuff);
				return;
			}

			// 读入内存中的图片
			this->tmpTexture = nullptr;

			HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(
				this->device, imageBuff, buffSize, tmpInfo->Width, tmpInfo->Height,
				D3DX_FROM_FILE, D3DPOOL_DEFAULT, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
				D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 0.0f), nullptr, nullptr, &(this->tmpTexture)
			);

			if(FAILED(hr)){
				Utility::Delete(imageBuff);
				return;
			}

			// 如果需要返回则填充内容
			if(info != nullptr){
				*info = *tmpInfo;
			}

			// 记录资源
			this->textureList.add(source, TextureInfo(this->tmpTexture, *tmpInfo));

			// 释放资源
			tmpInfo = nullptr;
			delete tmpInfo;
			Utility::Delete(imageBuff);

		}else{
			TextureInfo tmp = this->textureList.get(source);

			if(info != nullptr){
				*info = tmp.info;
			}

			this->tmpTexture = tmp.texture;
		}
	}

}