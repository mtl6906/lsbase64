#include "ls/Base64.h"
#include "iostream"

using ls::Base64;
using namespace std;

int main()
{
	Base64 base64;
	string b64, raw;
	base64.Encode("123", b64);
	cout << b64 << endl;
	base64.Decode(b64, raw);
	cout << raw << endl;
	return 0;
}
