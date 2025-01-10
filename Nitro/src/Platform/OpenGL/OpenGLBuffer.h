#pragma once

#include "Nitro/Renderer/Buffer.h"
#include <stdint.h>

namespace Nitro {

	/////////////////////////////////////////////////////////////////////
	/// INDEX-BUFFER ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);

	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};

	//////////////////////////////////////////////////////////////////////
	/// VERTEX-BUFFER ////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };

		static VertexBuffer* Create(float* vertices, uint32_t size);
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}