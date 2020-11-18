#include "iostream"
#include "ls/Base64.h"

using namespace std;

namespace ls
{
	Base64::Base64()
	{
		for(int i=0;i<26;++i)
		{
			characters[i] = 'A' + i;
			indexMapper[characters[i]] = i;
		}
		for(int i=26;i<52;++i)
		{
			characters[i] = 'a' + i - 26;
			indexMapper[characters[i]] = i;
		}
		for(int i=52;i<62;++i)
		{
			characters[i] = '0' + i - 52;
			indexMapper[characters[i]] = i;
		}
		indexMapper['+'] = 62;
		indexMapper['/'] = 63;
		characters[62] = '+';
		characters[63] = '/';
		characters[64] = '=';
	}
	int Base64::encode(const string &raw, string &base64)
	{
		int len = 4 * (raw.size() / 3 + 
				(raw.size() % 3 ? 1 : 0));
		base64.resize(len, '\0');
		int i, j;
		for(i=0, j=0;i<len-4;i+=4, j+=3)
		{
			base64[i] = characters[(raw[j] & 0xfc) >> 2];
			base64[i+1] = characters[((raw[j] & 0x03) << 4) + 
					((raw[j+1] & 0xf0) >> 4)];
			base64[i+2] = characters[((raw[j+1] & 0x0f) << 2) +
					((raw[j+2] & 0xc0) >> 6)];
			base64[i+3] = characters[raw[j+2] & 0x3f];
		}
		int last = raw.size() % 3;
		if(last == 0)
			last = 3;
		if(last > 0)
		{
			base64[i] = characters[(raw[j] & 0xfc) >> 2];
			base64[i+1] = (raw[j] & 0x03) << 4;
			base64[i+2] = 64;
			base64[i+3] = 64;
		}
		if(last > 1)
		{
			base64[i+1] += (raw[j+1] & 0xf0) >> 4;
			base64[i+2] = (raw[j+1] & 0x0f) << 2;
		}
		if(last > 2)
		{	
			base64[i+2] += (raw[j+2] & 0xc0) >> 6;
			base64[i+3] = raw[j+2] & 0x3f;
		}
		base64[i+1] = characters[base64[i+1]];
		base64[i+2] = characters[base64[i+2]];
		base64[i+3] = characters[base64[i+3]];
		return 0;
	}
	int Base64::decode(const string &base64, string &raw)
	{
		string index(base64.size(), '\0');
		int len = base64.size() / 4 * 3;
		int eq = 0;
		while(base64[len - eq + 1] == '=')
			++eq;
		raw.resize(len - eq);
		int i, j;
		for(i=0, j=0;i<len-3;i+=3, j+=4)
		{
			index[j] = indexMapper[base64[j]];
			index[j+1] = indexMapper[base64[j+1]];
			index[j+2] = indexMapper[base64[j+2]];
			index[j+3] = indexMapper[base64[j+3]];
	
			raw[i] = ((index[j] & 0x3f) << 2) + ((index[j+1] & 0x30) >> 4);
			raw[i+1] = ((index[j+1] & 0x0f) << 4) + ((index[j+2] & 0x3c) >> 2);
			raw[i+2] = ((index[j+2] & 0x03) << 6) + (index[j+3] & 0x3f);
		}
		if(eq < 3)
		{
			index[j] = indexMapper[base64[j]];
			index[j+1] = indexMapper[base64[j+1]];
			raw[i] = ((index[j] & 0x3f) << 2) + ((index[j+1] & 0x30) >> 4);
		}
		if(eq < 2)
		{
			index[j+2] = indexMapper[base64[j+2]];
			raw[i+1] = ((index[j+1] & 0x0f) << 4) + ((index[j+2] & 0x3c) >> 2);
		}
		if(eq < 1)
		{
			index[j+3] = indexMapper[base64[j+3]];
			raw[i+2] = ((index[j+2] & 0x03) << 6) + ((index[j+3] & 0x3f));
		}
		return 0;
	}
}
