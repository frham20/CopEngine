#include "cop.h"
#include "cop_camera.h"

namespace cop {

Camera::Camera()
	: m_position(0.0f, 0.0f, -5.0f),
	m_rotation(0.0f, 0.0f, 0.0f),
	m_viewDirty(true)
{
	SetLens(DirectX::XM_PIDIV4, 1.0f, 0.1f, 1000.0f);
}

void Camera::SetPosition(const DirectX::XMFLOAT3& position)
{
	m_position = position;
	m_viewDirty = true;
}

void Camera::SetRotation(const DirectX::XMFLOAT3& rotation)
{
	m_rotation = rotation;
	m_viewDirty = true;
}

void Camera::SetLens(float fovY, float aspectRatio, float zn, float zf)
{
	DirectX::XMStoreFloat4x4(&m_projMatrix, DirectX::XMMatrixPerspectiveFovLH(fovY, aspectRatio, zn, zf));
}

DirectX::XMFLOAT3 Camera::GetPosition() const
{
	return m_position;
}

DirectX::XMFLOAT3 Camera::GetRotation() const
{
	return m_rotation;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	if (m_viewDirty)
	{
		const_cast<Camera*>(this)->UpdateViewMatrix();
	}
	return DirectX::XMLoadFloat4x4(&m_viewMatrix);
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const
{
	return DirectX::XMLoadFloat4x4(&m_projMatrix);
}

void Camera::UpdateViewMatrix()
{
	using namespace DirectX;

	XMVECTOR pos = XMLoadFloat3(&m_position);
	XMVECTOR rot = XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

	XMVECTOR lookAt = XMVector3Rotate(XMVectorSet(0, 0, 1, 0), rot);
	XMVECTOR up = XMVector3Rotate(XMVectorSet(0, 1, 0, 0), rot);

	XMVECTOR target = XMVectorAdd(pos, lookAt);

	XMStoreFloat4x4(&m_viewMatrix, XMMatrixLookAtLH(pos, target, up));

	m_viewDirty = false;
}
} // namespace cp