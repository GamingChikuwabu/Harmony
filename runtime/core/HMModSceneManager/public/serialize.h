#pragma once
//#include <boost/describe.hpp>
//#include <boost/mp11.hpp>
//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/vector.hpp>
//#include <boost/archive/xml_iarchive.hpp>
//#include <boost/core/nvp.hpp>
//#include<vector>
//#include <sstream>
//#include <any>
//#include <Eigen/Dense>
//#include <Eigen/Geometry>
//#include <iostream>
//
//std::vector<std::string> inline split(const std::string& str, char delimiter) {
//    std::vector<std::string> tokens;
//    std::string token;
//    std::istringstream tokenStream(str);
//    while (std::getline(tokenStream, token, delimiter)) {
//        tokens.push_back(token);
//    }
//    return tokens;
//}
//
//namespace HARMONY
//{
//    namespace CORE
//    {
//        template<class Archive, class T,
//            class D1 = boost::describe::describe_bases<T, boost::describe::mod_public>,
//            class D2 = boost::describe::describe_bases<T,
//            boost::describe::mod_protected | boost::describe::mod_private>,
//            class D3 = boost::describe::describe_members<T,
//            boost::describe::mod_public | boost::describe::mod_protected>,
//            class D4 = boost::describe::describe_members<T, boost::describe::mod_private>,
//            class En = std::enable_if_t< boost::mp11::mp_empty<D2>::value&&
//            boost::mp11::mp_empty<D4>::value && !std::is_union<T>::value> >
//
//        void serialize(Archive& ar, T& t, boost::serialization::version_type)
//        {
//            int k = 0;
//
//            // public bases: use base_object
//
//            boost::mp11::mp_for_each<D1>([&](auto D) {
//
//                using B = typename decltype(D)::type;
//
//                char name[32];
//                std::sprintf(name, "base.%d", ++k);
//                ar& boost::make_nvp(name, boost::serialization::base_object<B>(t));
//
//                });
//
//            // public (and protected) members
//
//            boost::mp11::mp_for_each<D3>([&](auto D) {
//
//                try
//                {
//                    ar& boost::make_nvp(D.name, t.*D.pointer);
//                }
//                catch (const boost::archive::archive_exception& e) {
//                    std::cout << "Boost.Serializationアーカイブ例外: " << e.what() << std::endl;
//                }
//                catch (const std::exception& e) {
//                    std::cerr << "標準例外: " << e.what() << std::endl;
//                }
//                catch (...) {
//                    std::cerr << "未知の例外が発生しました。" << std::endl; 
//                }
//            });
//        }
//    }
//}
//
//// Eigenライブラリの型に対するシリアライズ関数を定義
//namespace boost {
//    namespace serialization {
//
//        template<class Archive>
//        void serialize(Archive& ar, Eigen::Vector3f& v, const unsigned int version) {
//            ar& make_nvp("x", v.x());
//            ar& make_nvp("y", v.y());
//            ar& make_nvp("z", v.z());
//        }
//
//        template<class Archive>
//        void serialize(Archive& ar, Eigen::Quaternion<float>& q, const unsigned int version) {
//            ar& make_nvp("w", q.w());
//            ar& make_nvp("x", q.x());
//            ar& make_nvp("y", q.y());
//            ar& make_nvp("z", q.z());
//        }
//
//    } // namespace serialization
//} // namespace boost