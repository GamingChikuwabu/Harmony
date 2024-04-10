#include"Transform.h"

namespace HARMONY
{
    namespace CORE
    {
        HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES(Transform)
            HM_ADD_PROPERTY_CLASS(Transform,_position),
            HM_ADD_PROPERTY_CLASS(Transform, _rotate),
            HM_ADD_PROPERTY_CLASS(Transform, _scale)
        HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES_END(Transform,Component)

        Transform::Transform()
        :_position(0.0f,0.0f,0.0f)
        ,_rotate(MATH::Quaternion::identity())
        ,_scale(0.0f,0.0f,0.0f)
        {
            
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