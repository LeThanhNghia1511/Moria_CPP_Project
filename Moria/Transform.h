#pragma once
#include "d3dx9.h"

class Transform
{
public:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

	Transform();
	~Transform();

	// Functions
	const D3DXMATRIX GetWorldMatrix();

};

