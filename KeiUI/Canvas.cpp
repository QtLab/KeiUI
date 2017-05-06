#include "Canvas.h"
#include "Window.h"

namespace KeiUI{
	Canvas::Canvas(IDirect3DDevice9* device, ID3DXSprite* sprite)
		: device(device), sprite(sprite), tmpTexture(nullptr), textureList(Array<string, TextureInfo>()), font(nullptr) 
	{
		ZeroMemory(&(this->oldFont), sizeof(D3DXFONT_DESC));
		ZeroMemory(&(this->newFont), sizeof(D3DXFONT_DESC));

		newFont.Height = 14;	//字体的高度
		newFont.Width = 0; // 不填由高度决定拉伸宽度
		newFont.Weight = 0;	// 加粗范围：0（光滑) 1000（粗体）
		newFont.MipLevels = D3DX_DEFAULT;
		newFont.Italic = false;	//斜体
		newFont.CharSet = DEFAULT_CHARSET;
		newFont.OutputPrecision = 0;
		newFont.Quality = 0;
		newFont.PitchAndFamily = 0;          
		//lstrcpy(fontDesc.FaceName, L"微软雅黑");	//字体

	}

	Canvas::~Canvas(){
		Utility::Release(this->font);

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

	void Canvas::drawRect(Rect rect, float depth, Clip clip, float rotation){

		if(rect.getTexture() != L""){
			this->loadTexture(rect.getTexture());

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

		this->sprite->Draw(this->tmpTexture, (clip.empty() ? nullptr : &(clip.toRECT())), nullptr, nullptr, rect.getColor().toD3DCOLOR());
	}

	void Canvas::drawStretch(Rect rect, float depth){

		D3DXIMAGE_INFO info;
		this->loadTexture(rect.getTexture(), &info);

		D3DXMATRIX positionMatrix, scaleMatrix, rotateMatrix, finalMatrix;
		D3DXMatrixRotationZ(&rotateMatrix, 0.0f);

		/*

		An example of decomposition:

		0|1|2	0,0 |15,0 |30,0
		3|4|5	0,15|15,15|30,15
		6|7|8	0,30|15,30|30,30

		*/

		float width = info.Width / 3;
		float height = info.Height / 3;
		Clip clip(0, 0, width, height);	// Set the corner 0 at the same time

		for(int i = 0; i < 9; i++){
			int x = 0, y = 0;
			float scaleX = 1.0f, scaleY = 1.0f;

			switch(i){
			case 2:	// Four corners
				
				clip.setX(width * 2);
				clip.setY(0);
				
				x = rect.getWidth() - width;
				break;

			case 6:
				clip.setX(0);
				clip.setY(height * 2);
				
				y = rect.getHeight() - height;
				break;

			case 8:
				clip.setX(width * 2);
				clip.setY(height * 2);
				
				x = rect.getWidth() - width;
				y = rect.getHeight() - height;
				break;

			case 1:	// Up and down the two corners
				clip.setX(width);
				clip.setY(0);
				
				x = width;

				scaleX = (rect.getWidth() - width * 2) / width;
				break;

			case 7:
				clip.setX(width);
				clip.setY(height * 2);
				
				x = width;
				y = rect.getHeight() - height;

				scaleX = (rect.getWidth() - width * 2) / width;
				break;

			case 3:	// Left and right the two corners
				clip.setX(0);
				clip.setY(height);

				y = height;

				scaleY = (rect.getHeight() - height * 2) / height;
				break;

			case 5:
				clip.setX(width * 2);
				clip.setY(height);
				
				x = rect.getWidth() - width;
				y = height;

				scaleY = (rect.getHeight() - height * 2) / height;
				break;

			case 4:	// Middle corner
				clip.setX(width);
				clip.setY(height);

				x = width;
				y = height;

				scaleX = (rect.getWidth() - width * 2) / width;
				scaleY = (rect.getHeight() - height * 2) / height;
				break;
			}

			D3DXMatrixScaling(&scaleMatrix, scaleX * rect.getScale(), scaleY * rect.getScale(), 0.0f);
			D3DXMatrixTranslation(&positionMatrix, rect.getX() + x * Window::resolution, rect.getY() + y * Window::resolution, depth);
			finalMatrix = scaleMatrix * rotateMatrix * positionMatrix;
			this->sprite->SetTransform(&finalMatrix);

			this->sprite->Draw(this->tmpTexture, &(clip.toRECT()), nullptr, nullptr, rect.getColor().toD3DCOLOR());
		}
	}

	void Canvas::drawFont(Font font){

		this->newFont.Height = font.getSize();
		this->newFont.Weight = font.getBold() ? 1000 : 0;

		if(memcmp(&(this->newFont),&(this->oldFont),sizeof(D3DXFONT_DESC)) != 0){
			Utility::Release(this->font);

			if(FAILED(D3DXCreateFontIndirect(device, &(this->newFont), &(this->font)))){
				return;
			}

			this->oldFont = this->newFont;
		}

		RECT rect = font.getRect().toRECT();
		D3DCOLOR color = font.getColor().toD3DCOLOR();

		this->font->DrawText(nullptr, font.getText().c_str(), -1, &rect, DT_WORDBREAK | DT_CENTER | DT_VCENTER, color);
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
						int index = j * 4 + i * lockedRect.Pitch;
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