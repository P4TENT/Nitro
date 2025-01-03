#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Nitro {
	class NITRO_API Layer
	{
	private:
		std::string m_Name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_Name; }
	};
}