#include "Texture.h"

Texture::Texture()
{
	_texture = nullptr;
}

bool Texture::Load(LPDIRECT3DDEVICE9 device, std::wstring filePath)
{
    HRESULT hr = D3DXCreateTextureFromFileExW(
        device,
        filePath.c_str(),      // Đường dẫn file (Unicode)
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
        D3DX_FILTER_NONE,
        D3DX_FILTER_NONE,
        0,              // Color key (màu trong suốt, thường để 0 nếu file .png đã có alpha)
        &_info,          // Lưu thông tin ảnh vào biến info
        NULL,
        &_texture        // Đổ dữ liệu vào con trỏ texture
    );

    return SUCCEEDED(hr);
}

void Texture::Render(LPD3DXSPRITE handler, RECT* srcRect, D3DXVECTOR3* localOffset, D3DCOLOR color)
{
    if (handler && _texture)
    {
        // Tinh toan vi tri trung tam (cua sprite)
        D3DXVECTOR3 center(0, 0, 0);

        // GameObj co animation
        if (srcRect != nullptr) {
            center.x = (float)(srcRect->right - srcRect->left) / 2.0f;
            center.y = (float)(srcRect->bottom - srcRect->top) / 2.0f;
        }
        // GameObj tinh, ko co animation (anh ko bi cat)
        else {
            center.x = (float)_info.Width / 2.0f;
            center.y = (float)_info.Height / 2.0f;
        }

        // Vi tri ve GameObj
        D3DXVECTOR3 finalOffset(0, 0, 0); // Mặc định vẽ tại tâm Ma trận
        if (localOffset != nullptr)
        {
            finalOffset = *localOffset; // Nếu có truyền offset thì xài
        }

        // Goi lenh ve
        handler->Draw(_texture, srcRect, &center, &finalOffset, color);
    }
}


Texture::~Texture()
{
	if (_texture)
	{
		_texture->Release();
		_texture = nullptr;
	}
}