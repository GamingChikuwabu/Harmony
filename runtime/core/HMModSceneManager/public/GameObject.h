#pragma once
#include<string>
#include<list>
#include"Transform.h"
#include"GameObject.generate.h"

namespace HARMONY
{
	namespace CORE
	{
		HMCLASS()
		class HMMODSCENEMANAGER_API GameObject :public HMObject
		{
			HM_CLASS_BODY()
		public:
			GameObject();
			~GameObject();
			// Transformのゲッターとセッター
			inline void setTransform(Transform* transform) { _transform = transform; }
			inline Transform* getTransform() const { return _transform; }

			// Nameのゲッターとセッター
			inline void setName(const HMString& name) { _name = name; }
			inline HMString getName() const { return _name; }

			// Tagのゲッターとセッター
			inline void setTag(const HMString& tag) { _tag = tag; }
			inline HMString getTag() const { return _tag; }

			// Layerのゲッターとセッター
			inline void setLayer(const HMString& layer) { _layer = layer; }
			inline HMString getLayer() const { return _layer; }

			template<class T>
			T* GetComponent();

			template<class T>
			T* AddComponent();
		protected:
			Transform* _transform;
			HMPROPERTY()
			HMString _name;
			HMPROPERTY()
			HMString _tag;
			HMPROPERTY()
			HMString _layer;
			HMPROPERTY()
			HMArray<Component*> m_componentList;
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
			m_componentList.Add(new T());
			Component* comp = static_cast<Component*>(m_componentList.Back());
			comp->_gameObject = this;
			return (T*)comp;
		}
	}
}