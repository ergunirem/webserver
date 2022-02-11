#include "HTTPRequestMethods.hpp"

namespace HTTPRequest {

	namespace {
		const char* existing_methods_list[] = {"GET", "POST", "HEAD", "DELETE", "PUT", "CONNECT", "OPTIONS", "TRACE", "PATCH"};
	}
    std::set<std::string> HTTPRequestMethods(existing_methods_list, existing_methods_list + sizeof(existing_methods_list) / sizeof(existing_methods_list[0]));
}
