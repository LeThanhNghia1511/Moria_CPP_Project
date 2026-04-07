#include "Transform.h"

Transform::Transform()
{
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{

}

const D3DXMATRIX Transform::GetWorldMatrix()
{
    D3DXMATRIX worldMatrix;
    D3DXMatrixIdentity(&worldMatrix);

    D3DXMATRIX scaleMatrix, rotationZMatrix, translationMatrix;

    D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, 1.0f);
    D3DXMatrixRotationZ(&rotationZMatrix, rotation.z);
    D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);

    worldMatrix = scaleMatrix * rotationZMatrix * translationMatrix;
    return worldMatrix;
}