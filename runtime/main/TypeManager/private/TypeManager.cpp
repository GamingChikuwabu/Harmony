#include"TypeManager.h"


namespace HARMONY
{
    bool TypeManager::Init()
    {
        DETAIL::ItemCreator::CreateType<int>("int");
        DETAIL::ItemCreator::CreateType<unsigned int>("unsigned_int");
        DETAIL::ItemCreator::CreateType<float>("float");
        DETAIL::ItemCreator::CreateType<long long>("longlong");
        DETAIL::ItemCreator::CreateType<double>("double");
        DETAIL::ItemCreator::CreateType<char>("char");
        DETAIL::ItemCreator::CreateType<bool>("bool");
        DETAIL::ItemCreator::CreateType<short>("short");

        return false;
    }
}