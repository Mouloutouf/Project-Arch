#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Alpha.h"

#include "GameObject.h"
#include "Component.h"

///\

#include "RenderObject.h"
#include "Display.h"

namespace alpha
{
	namespace core
	{
		template <typename T = RenderObject>
		class Renderer : public Component
		{
		public:

			Renderer();
			Renderer(GameObject* _gameObject, Display* _display, int _ppu = 1, __Layer _layer = Layers::DEFAULT_LAYER);
			Renderer(const Renderer& that, GameObject* _gameObject);

			~Renderer();

			Renderer<T>* Clone(GameObject* _gameObject) override;

			virtual T* CreateRenderObject(int _ppu, __Layer _layer);

			void SetActive(bool _value) override;

			void AddToRender();

			void SetLayer(__Layer _layer);
			__Layer GetLayer();

			void SetOrderInLayer(int _order);
			int GetOrderInLayer();

		protected:

			T* renderObject = nullptr;

			Display* display = nullptr;
		};

		template<typename T>
		Renderer<T>::Renderer()
		{
		}
		template<typename T>
		Renderer<T>::Renderer(GameObject* _gameObject, Display* _display, int _ppu, __Layer _layer)
			: Component(_gameObject), display(_display)
		{
			CreateRenderObject(_ppu, _layer);

			AddToRender();
		}
		template<typename T>
		Renderer<T>::Renderer(const Renderer& that, GameObject* _gameObject)
			: Component(_gameObject), display(that.display)
		{
			renderObject = new T(*that.renderObject);

			AddToRender();
		}

		template<typename T>
		Renderer<T>::~Renderer()
		{
			delete renderObject;
		}

		template<typename T>
		Renderer<T>* Renderer<T>::Clone(GameObject* _gameObject)
		{
			return new Renderer<T>(*this, _gameObject);
		}

		template<typename T>
		T* Renderer<T>::CreateRenderObject(int _ppu, __Layer _layer)
		{
			renderObject = new T(_ppu);
			renderObject->layer = _layer;

			return renderObject;
		}

		template<typename T>
		void Renderer<T>::SetActive(bool _value)
		{
			Component::SetActive(_value);
			renderObject->render = _value;
		}

		template<typename T>
		void Renderer<T>::AddToRender()
		{
			auto& tags = *(gameObject->GetTagsList());
			for (int i = 0; i < tags.size(); i++) {
				if (tags[i] == Tag::Prefab)
					return;
			} display->AddObjectToRender(gameObject, renderObject);
		}

		template<typename T>
		void Renderer<T>::SetLayer(__Layer _layer)
		{
			renderObject->layer = _layer;

			display->RemoveObjectToRender(renderObject);
			AddToRender();
		}
		template<typename T>
		__Layer Renderer<T>::GetLayer() { return renderObject->layer; }

		template<typename T>
		void Renderer<T>::SetOrderInLayer(int _order) { renderObject->orderInLayer = clamp(_order, 0, 9999); }
		template<typename T>
		int Renderer<T>::GetOrderInLayer() { return renderObject->orderInLayer; }
	}
}

#endif // !RENDERER_H
