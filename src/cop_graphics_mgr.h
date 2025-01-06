#pragma once

namespace cop {
class GraphicsMgr
{
public:
	GraphicsMgr() = default;
	~GraphicsMgr() = default;

	bool Initialize(HWND hwnd);
	void Shutdown();

	void Render();
	float GetFrameTime();
	void ResizeBuffers(int width, int height);

protected:
	void BeginFrame();
	void EndFrame();

	void WaitForGPU();

private:
	GraphicsMgr(const GraphicsMgr&) = delete;
	GraphicsMgr& operator=(const GraphicsMgr&) = delete;
	
	Microsoft::WRL::ComPtr<ID3D12Device> m_device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[2];
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
	Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
	HANDLE m_fenceEvent;
	UINT m_rtvDescriptorSize;
	UINT m_frameIndex;
	UINT64 m_fenceValue;
	Timer m_frameTimer;
};

extern GraphicsMgr g_GraphicsMgr;
}