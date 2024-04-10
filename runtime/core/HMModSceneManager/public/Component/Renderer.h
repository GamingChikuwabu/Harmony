#pragma once
#include"Component.h"
#include"IVertexBuffer.h"
#include"IConstantBuffer.h"
#include"IIndexBuffer.h"
#include"IMaterial.h"

namespace HARMONY
{
    namespace CORE
    {
        HMCLASS()
        class HMMODSCENEMANAGER_API Renderer : public Component
        {
        public:
            Renderer();
            ~Renderer();
        protected:
            virtual void OnRender(const class ICommandBuffer* commandbuffer);
        };
    }
}