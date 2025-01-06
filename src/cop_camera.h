#pragma once

namespace cop {

class Camera
{
public:
    Camera();

    // Setters
    void SetPosition(const XMFLOAT3& position);
    void SetRotation(const XMFLOAT3& rotation);
    void SetLens(float fovY, float aspectRatio, float zn, float zf);

    // Getters
    XMFLOAT3 GetPosition() const;
    XMFLOAT3 GetRotation() const;
    XMMATRIX GetViewMatrix() const;
    XMMATRIX GetProjectionMatrix() const;

    // Utility
    void UpdateViewMatrix();

private:
    // Camera parameters
    XMFLOAT3 m_position;
    XMFLOAT3 m_rotation;

    // Matrices
    XMFLOAT4X4 m_viewMatrix;
    XMFLOAT4X4 m_projMatrix;

    bool m_viewDirty;
};

}