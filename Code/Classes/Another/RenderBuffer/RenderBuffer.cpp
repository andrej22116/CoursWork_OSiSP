#include "stdafx.h"
#include "RenderBuffer.h"

namespace explorer {
	RenderBuffer::RenderBuffer(HWND hWnd, int width, int height) : _hWnd(hWnd), _width(width), _height(height)
	{
		_hDC_Device = GetDC(_hWnd);
		_hDC_Buffer = CreateCompatibleDC(_hDC_Device);
		_hBitmap = CreateCompatibleBitmap(_hDC_Device, _width, _height);
		SelectObject(_hDC_Buffer, _hBitmap);
	}
	RenderBuffer::~RenderBuffer()
	{
		DeleteObject(_hBitmap);
		DeleteDC(_hDC_Buffer);
		ReleaseDC(_hWnd, _hDC_Device);
	}


	HDC RenderBuffer::getDC()
	{
		return _hDC_Buffer;
	}
	HBITMAP RenderBuffer::getHBitmap()
	{
		return _hBitmap;
	}
	int RenderBuffer::getWidth() { return _width; }
	int RenderBuffer::getHeight() { return _height; }

	void RenderBuffer::resizeBuffer(int width, int height)
	{
		HDC hDC = CreateCompatibleDC(_hDC_Device);
		HBITMAP hBitmap = CreateCompatibleBitmap(_hDC_Device, width, height);
		SelectObject(hDC, hBitmap);

		BitBlt(hDC, 0, 0, _width, _height, _hDC_Buffer, 0, 0, SRCCOPY);

		_width = width;
		_height = height;
		DeleteDC(_hDC_Buffer);
		DeleteObject(_hBitmap);

		_hDC_Buffer = hDC;
		_hBitmap = hBitmap;
	}

	void RenderBuffer::copyTo(RenderBuffer& buffer)
	{
		int bufferWidth = buffer.getWidth();
		int bufferHeight = buffer.getHeight();

		int width = 0;
		int height = 0;
		if (_width < bufferWidth || _height < bufferHeight) {
			width = _width;
			height = _height;
		}
		else {
			width = bufferWidth;
			height = bufferHeight;
		}
		m_copyTo(buffer, 0, 0, 0, 0, width, height);
	}
	void RenderBuffer::copyTo(RenderBuffer& buffer, int toX, int toY)
	{
		int bufferWidth = buffer.getWidth();
		int bufferHeight = buffer.getHeight();

		int width = 0;
		int height = 0;
		if (_width < bufferWidth || _height < bufferHeight) {
			width = _width;
			height = _height;
		}
		else {
			width = bufferWidth;
			height = bufferHeight;
		}
		m_copyTo(buffer, 0, 0, toX, toY, width, height);
	}
	void RenderBuffer::copyTo(RenderBuffer& buffer, int toX, int toY, int width, int height)
	{
		m_copyTo(buffer, 0, 0, toX, toY, width, height);
	}
	void RenderBuffer::copyTo(RenderBuffer& buffer, int fromX, int fromY, int toX, int toY, int width, int height)
	{
		m_copyTo(buffer, fromX, fromY, toX, toY, width, height);
	}
	void RenderBuffer::copyTo(HDC device)
	{
		int width = _width;
		int height = _height;
		m_copyTo(device, 0, 0, 0, 0, width, height);
	}
	void RenderBuffer::copyTo(HDC device, int toX, int toY)
	{
		int width = _width;
		int height = _height;
		m_copyTo(device, 0, 0, toX, toY, width, height);
	}
	void RenderBuffer::copyTo(HDC device, int toX, int toY, int width, int height)
	{
		m_copyTo(device, 0, 0, toX, toY, width, height);
	}
	void RenderBuffer::copyTo(HDC device, int fromX, int fromY, int toX, int toY, int width, int height)
	{
		m_copyTo(device, fromX, fromY, toX, toY, width, height);
	}

	void RenderBuffer::m_copyTo(RenderBuffer& buffer, int fromX, int fromY, int toX, int toY, int width, int height)
	{
		if (width + fromX > _width || width + toX > buffer.getWidth()) {
			return;
		}
		else if (height + fromY > _height || height + toY > buffer.getHeight()) {
			return;
		}
		BitBlt(buffer.getDC(), toX, toY, width, height, _hDC_Buffer, fromX, fromY, SRCCOPY);
	}

	void RenderBuffer::m_copyTo(HDC device, int fromX, int fromY, int toX, int toY, int width, int height)
	{
		BitBlt(device, toX, toY, width, height, _hDC_Buffer, fromX, fromY, SRCCOPY);
	}
}