#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size_)
	: dataID(0), size(size_)
{
	GlCall(glGenBuffers(1, &dataID));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, dataID));
	GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &dataID);
}

void VertexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, dataID));
}

void VertexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetData(void* newData)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, newData);
}