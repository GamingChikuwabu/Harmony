#include"Transform.h"

namespace HARMONY
{
    namespace CORE
    {
        Transform::Transform()
        {
            //reset();
        }
        Transform::~Transform()
        {
        }

        void Transform::setRotationFromPYR(float pitch, float yaw, float roll)
        {
        }

        MATH::Matrix4x4 Transform::getWorldTransformMatrix() const
        {
            return MATH::Matrix4x4();
        }

        void Transform::reset()
        {
            
        }
    }
}