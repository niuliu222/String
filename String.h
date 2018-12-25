#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
namespace LLD {
	namespace BaseString {
		template <class T>
		class BaseString : public std::basic_string<T, std::char_traits<T>, std::allocator<T>> {
		public:
			using SupperType = std::basic_string<T, std::char_traits<T>, std::allocator<T>>;
			typedef void(*Callback)(const SupperType &, int idx);

			BaseString(const SupperType & value):SupperType(value){}
			BaseString(){}

			void Split(const SupperType & splitter, Callback callback) {
				int index = this->find(splitter);
				int current_idx = 0;
				int ArrIndex = 0;
				int lenth = 0;
				while (index >= 0) {
					lenth = index - current_idx;
					if (lenth > 0) {
						SupperType value = this->substr(current_idx, lenth);
						callback(value, ArrIndex);
					}
					++ArrIndex;
					current_idx = index + splitter.length();
					index = this->find(splitter, current_idx);
				}

				if (current_idx < this->length()) {
					SupperType value = this->substr(current_idx);
					callback(value, ArrIndex);
				}
			}

			void Split(const SupperType & splitter, std::vector<SupperType> & out) {
				Split(splitter, [&out](const SupperType &str, int idx) {
					out.push_back(str);
				});
			}
			void Split(const SupperType & splitter, std::vector<std::shared_ptr<SupperType>> & out) {
				Split(splitter, [&out](const SupperType &str, int idx) {
					std::shared_ptr<SupperType> ptr = std::make_shared<SupperType>(new SupperType(str));
					out.push_back(ptr);
				});
			}


			void Replace(const SupperType & str_old, const SupperType & str_New) {
				while (true) {
					int pos = 0;
					if ((pos = this->find(str_old)) >= 0)
						this->replace(pos, str_old.length(), str_New);
					else   break;
				}
			}
			void Trim() {
				Replace(" ", "");
				Replace("\n", "");
				Replace("\t", "");
			}
		};
		
		/*
		template <class T, bool iswchar = false>
		BaseString<T> Format(unsigned int size, const char * format, ...) {
			char arr[size] = { 0 };
			sprintf(arr, format, ...);
			using stringstream = std::basic_stringstream<T, std::char_traits<T>, std::allocator<T>>;
			stringstream stream;
			if (iswchar) {
				std::wstring str = arr;
				stream << str;
			}
			else {
				std::string str = arr;
				stream << str;
			}
			return BaseString<T>(stream.str());
		}*/
		
	}

	//namespace String {
		using String	= BaseString::BaseString<char>;
		using WString	= BaseString::BaseString<wchar_t>;
		/*auto  Format	= BaseString::Format<char, false>;
		auto  WFormat	= BaseString::Format<wchar_t, true>;*/
	//}
	
}