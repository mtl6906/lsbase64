#ifndef LS_BASE64_H
#define LS_BASE64_H

#include "string"
#include "map"

namespace ls
{
	class Base64
	{
		char characters[65];
		std::map<char, int> indexMapper;
		public:
			Base64();
			int encode(const std::string &raw, std::string &base64);
			int decode(const std::string &base64, std::string &raw);
	};
}


#endif
