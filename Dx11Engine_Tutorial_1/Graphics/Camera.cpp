#include "Camera.h"

using namespace DirectX;


Camera::Camera()
{
	this->pos = XMFLOAT3(0.f, 0.f, 0.f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.f, 0.f, 0.f);
	this->rotVector = XMLoadFloat3(&this->rot);
	UpdateViewMatrix();

}

void Camera::SetProjectionValues(float fovDgree, float aspectRatio, float nearZ, float farZ)
{
	float fovRadiands = (fovDgree / 360.f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadiands, aspectRatio, nearZ, farZ);
}

const XMMATRIX& Camera::GetViewMatrix() const
{
	return this->viewMatrix;
}

const XMMATRIX& Camera::GetProjectionMatrix() const
{
	return this->projectionMatrix;
}

const XMFLOAT3& Camera::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR& Camera::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3& Camera::GetRotationFloat3() const
{
	return this->rot;
}

const XMVECTOR& Camera::GetRotationVector() const
{
	return this->rotVector;
}

void Camera::SetPosition(const XMVECTOR &  pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}



void Camera::SetRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(*this->rot);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{	
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMMATRIX camRoatationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);

	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRoatationMatrix);
	camTarget += this->posVector;

	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRoatationMatrix);
	
	this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);
}
