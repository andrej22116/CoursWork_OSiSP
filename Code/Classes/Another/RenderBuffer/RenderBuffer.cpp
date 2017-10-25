#include "stdafx.h"
#include "RenderBuffer.h"

namespace explorer {
	RenderBuffer::RenderBuffer(HDC hDC, int width, int hieght)
	{
		_hDC_Device = hDC;
		_hDC_Buffer = CreateCompatibleDC(_hDC_Device);
		_hBitmap = CreateCompatibleBitmap(_hDC_Device, width, hieght);
		SelectObject(_hDC_Buffer, _hBitmap);
	}
	RenderBuffer::~RenderBuffer()
	{
		DeleteObject(_hBitmap);
		DeleteDC(_hDC_Buffer);
	}


	HDC RenderBuffer::getDC()
	{
		return _hDC_Buffer;
	}
	HBITMAP RenderBuffer::getHBitmap()
	{
		return _hBitmap;
	}
	void RenderBuffer::resizeBuffer(int width, int hieght)
	{
		HDC hDC = CreateCompatibleDC(_hDC_Device);
		HBITMAP hBitmap = CreateCompatibleBitmap(_hDC_Device, width, hieght);
		BitBlt(hDC, 0, 0, _width, _height, _hDC_Buffer, 0, 0, SRCCOPY);
	}

	void RenderBuffer::copyTo(RenderBuffer& buffer)
	{

	}
	void RenderBuffer::copyTo(RenderBuffer& buffer, int x, int y)
	{

	}
	void RenderBuffer::copyTo(RenderBuffer& buffer, int x, int y, int width, int hieght)
	{

	}
}