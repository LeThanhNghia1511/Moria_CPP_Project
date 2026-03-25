#include "Texture.h"

Texture::Texture()
{
	_texture = nullptr;
}

bool Texture::Load(LPDIRECT3DDEVICE9 device, std::wstring filePath, int width, int height)
{
    HRESULT hr = D3DXCreateTextureFromFileExW(
        device,
        filePath.c_str(),      // Đường dẫn file (Unicode)
        width,  // Chiều rộng (giữ nguyên gốc)
        height,  // Chiều cao (giữ nguyên gốc)
        1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
        D3DX_FILTER_POINT, D3DX_FILTER_NONE,
        0,              // Color key (màu trong suốt, thường để 0 nếu file .png đã có alpha)
        &_info,          // Lưu thông tin ảnh vào biến info
        NULL,
        &_texture        // Đổ dữ liệu vào con trỏ texture
    );

    return SUCCEEDED(hr);
}

void Texture::Render(LPD3DXSPRITE spriteHandler, RECT* sourceRect, D3DXVECTOR3* position, D3DCOLOR color)
{
    spriteHandler->Draw(
        _texture,
        sourceRect,    // Cắt ảnh ở đây
        NULL,          // Center (thường để NULL để lấy góc trên trái 0,0 làm gốc)
        position,      // Vị trí trên màn hình
        color          // Màu hòa trộn (trắng = giữ nguyên gốc)
    );
}


Texture::~Texture()
{
	if (_texture)
	{
		_texture->Release();
		_texture = nullptr;
	}
}