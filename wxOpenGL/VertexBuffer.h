#pragma once
#include "glall.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, size_t size_);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(void* newData);

private:
	unsigned int dataID;
	size_t size;
};