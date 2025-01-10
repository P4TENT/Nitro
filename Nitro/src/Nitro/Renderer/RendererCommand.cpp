#include "ngpch.h"

#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nitro {
	RenderAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}