#pragma once
#include<string>
#include<list>
#include"Transform.h"

namespace HARMONY
{
	namespace CORE
	{
		class GameObject
		{
		public:
			GameObject();
			~GameObject();
			// Transformのゲッターとセッター
			inline void setTransform(Transform* transform) { _transform = transform; }
			inline Transform* getTransform() const { return _transform; }

			// Nameのゲッターとセッター
			inline void setName(const std::string& name) { _name = name; }
			inline std::string getName() const { return _name; }

			// Tagのゲッターとセッター
			inline void setTag(const std::string& tag) { _tag = tag; }
			inline std::string getTag() const { return _tag; }

			// Layerのゲッターとセッター
			inline void setLayer(const std::string& layer) { _layer = layer; }
			inline std::string getLayer() const { return _layer; }

			template<class T>
			T* GetComponent();

			template<class T>
			T* AddComponent();
		protected:
			Transform* _transform;
			std::string _name;
			std::string _tag;
			std::string _layer;
			std::list<Component*> m_componentList;
		};

		template<class T>
		inline T* GameObject::GetComponent()
		{
			for (auto comp : m_componentList)
			{
				T* temp_comp = dynamic_cast<T*>(comp);
				if (temp_comp)
				{
					return temp_comp;
				}
			}
			return nullptr;
		}

		template<class T>
		inline T* GameObject::AddComponent()
		{
			m_componentList.push_back(new T());
			Component* comp = static_cast<Component*>(m_componentList.back());
			comp->_gameObject = this;
			return (T*)comp;
		}
	}
}