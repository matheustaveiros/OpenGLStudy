#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();

	unsigned int offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, layout.GetStride(), (const void*)offset));
		offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
