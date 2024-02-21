#pragma once
#include<bitset>

namespace HARMONY
{
    namespace DETAIL
    {
        
        /// @brief �^�̎��
        enum class type_trait_infos : size_t
        {
            is_class = 0,
            is_enum,
            is_array,
            is_pointer,
            is_arithmetic,
            is_function_pointer,
            is_member_object_pointer,
            is_member_function_pointer,
            is_associative_container,
            is_sequential_container,
            is_template_instantiation,
            is_wrappermapper,
            TYPE_TRAIT_COUNT
        };

        // access_level�̒l�̐����擾
        constexpr size_t type_trait_count = static_cast<size_t>(type_trait_infos::TYPE_TRAIT_COUNT);

        using TypeTraitBitSet = std::bitset<type_trait_count>;

        /// @brief �n���ꂽ�^�̃r�b�g�𗧂Ă�
        /// @tparam T ���ׂ�^
        /// @return bit
        template<typename T>
        TypeTraitBitSet GetBitSet()
        {
            std::bitset<type_trait_count> retBit;
            // �Z�p�^�̏ꍇ
            if constexpr (std::is_arithmetic_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_arithmetic));
            }
            // �N���X�̏ꍇ
            if constexpr (std::is_class_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_class));
            }
            // �񋓌^�̏ꍇ
            if constexpr (std::is_enum_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_enum));
            }
            // �z��̏ꍇ
            if constexpr (std::is_array_v<std::remove_cv_t<std::remove_pointer_t<T>>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_array));
            }
            // �|�C���^�̏ꍇ
            if constexpr (std::is_pointer_v<T>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_pointer));
            }
            // �֐��|�C���^�̏ꍇ
            if constexpr (std::is_function_v<std::remove_pointer_t<T>>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_function_pointer));
            }
            // �����o�I�u�W�F�N�g�|�C���^�̏ꍇ
            if constexpr (std::is_member_object_pointer_v<T>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_member_object_pointer));
            }
            // �����o�֐��|�C���^�̏ꍇ
            if constexpr (std::is_member_function_pointer_v<T>) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_member_function_pointer));
            }
            // ���b�p�[�^�C�v���ǂ���
            if constexpr (is_wrapper<T>::value) {
                retBit.set(static_cast<std::size_t>(type_trait_infos::is_wrappermapper));
            }
            return retBit; 
        }
    }
}