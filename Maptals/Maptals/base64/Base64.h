

#ifndef BASE64_H
#define BASE64_H
#include <string>
//! Consolidated into one file by John Dunham 7-24-12
class Base64
{
public:
    static std::string base64_encode(unsigned char const* , unsigned int len);
    static std::string base64_decode(std::string const& s);
};

#endif
