macro(Build_Init targetname)
    # private�t�H���_�̒�����.cpp�t�@�C����S�Ď擾
    file(GLOB_RECURSE SOURCES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp")
    file(GLOB_RECURSE SOURCES_PRIVATE_H "${CMAKE_CURRENT_SOURCE_DIR}/private/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/private/*.hpp")
    file(GLOB_RECURSE SOURCES_PUBLIC_H "${CMAKE_CURRENT_SOURCE_DIR}/public/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/public/*.hpp")
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/public)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/public/ DESTINATION include)

    if(SOURCES_CPP)  # �C��: �ϐ���W�J���Ȃ�
        message(STATUS "Found cpp files: ${SOURCES_CPP}")  # �C��: �ǉ��̃��b�Z�[�W�^�C�v
        add_library(${targetname} SHARED ${SOURCES_CPP} ${SOURCES_PRIVATE_H} ${SOURCES_PUBLIC_H})
        
        string(TOUPPER ${targetname} target_upper)
        # Windows�ȊO�̏ꍇ�͋�̒�`���g�p
        if(NOT WIN32)
            set(EXPORT_DLL "")
            set(IMPORT_DLL "")
        else()
            # Windows�̏ꍇ��__declspec��ݒ�
            set(EXPORT_DLL "__declspec(dllexport)")
            set(IMPORT_DLL "__declspec(dllimport)")
        endif()

        # �r���h���郉�C�u�������̂ɂ�EXPORT_DLL���g�p
        target_compile_definitions(${targetname} PRIVATE ${target_upper}_API=${EXPORT_DLL})
        target_compile_definitions(${targetname} INTERFACE ${target_upper}_API=${IMPORT_DLL})
        message(STATUS "${target_upper}_API set to: ${EXPORT_DLL}")  # �C��: �ǉ��̃��b�Z�[�W�^�C�v
    endif()
endmacro()