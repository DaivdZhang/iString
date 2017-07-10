#include <iostream>
#include "istring.h"

using namespace istring;

size_t* next(const char* s);

String::String()
{
    _length = 0;
    _str = new char[1]{'\0'};
}


String::String(const char c)
{
    _length = 1;
    _str = new char[2]{c};
    _str[1] = '\0';
}


String::String(const char* s)
{
    _length = strlen(s);
    _str = new char[_length + 1];
    strcpy_s(_str, _length + 1, s);
}


String::String(const String& s)
{
    _length = s._length;
    _str = new char[_length + 1];
    strcpy_s(_str, _length + 1, s._str);
}


String::String(size_t n, const char c)
{
    _length = n;
    _str = new char[_length + 1]{c};
    if(!_str)
        exit(14);
    _str[_length] = '\0';
}


String::String(size_t n, const char* s)
{
    _length = n*strlen(s);
    _str = new char[_length + 1]{'\0'};
    if(!_str)
        exit(14);
    for(size_t i = 0; i < n; i++)
        strcat_s(_str, _length + 1, s);
}


String::~String()
{   
    delete[] _str;
}


String& String::operator=(const String& s)
{
    if(this != &s)
    {
        _length = s._length;

        if(_str)
            delete[] _str;

        _str = new char[_length + 1];
        strcpy_s(_str, _length + 1, s._str);
    }
    return *this;
}


bool String::operator==(const String& s) const
{
    if(this->_length != s._length)
        return false;

    for(size_t i = 0; i < s._length; i++)
    {
        if(this->_str[i] != s._str[i])
            return false;
    }
    return true;
}


bool String::operator!=(const String& s) const
{
    if(*this == s)
        return false;
    else
        return true;
}


const char& String::operator[](size_t i) const
{
    return _str[i];
}


String String::operator+(const String& s) const
{
    char* _s = new char[s._length + _length + 1]{'\0'};
    if(!_s)
        exit(14);
    strcpy_s(_s, _length + 1, _str);
    strcat_s(_s, _length + s._length + 1, s._str);
    String _(_s);
    delete[] _s;
    return _;
}


String String::operator*(const size_t n) const
{
    if(!n)
        return String("");
    else
    {
        char* _s = new char[_length*n + 1]{'\0'};
        if(!_s)
            exit(14);
        for(size_t i = 0; i < n; i++)
            strcat_s(_s, _length*n + 1, _str);
        String _(_s);
        delete[] _s;
        return _;
    }
}


size_t String::length() const
{
    return _length;
}


char * String::_data() const
{
    return _str;
}


bool String::empty() const
{
    return _length ? true : false;
}


long long String::find(const char c) const
{
    for(size_t i = 0; i < _length; i++)
        if(_str[i] == c)
            return i;
    return -1;
}


long long String::find(const char* pattern) const
{
    auto next_array = next(pattern);
    auto p_length = strlen(pattern);
    size_t i = 0;
    size_t j = 0;
    while(i < _length)
    {
        if(_str[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if(!j)
            {
                i++;
                continue;
            }
            j = next_array[j - 1];
        }
        if(j == p_length)
        {
            delete[] next_array;
            return i - p_length;
        }
    }
    delete[] next_array;
    return -1;
}


inline size_t* next(const char* s)
{
    auto s_length = strlen(s);
    auto next = new size_t[s_length]{0};
    if(next == nullptr)
        exit(14);
    for(size_t i = 1, j = 0; i < s_length;)
    {
        if(s[i] == s[j])
        {
            next[i] = j + 1;
            i++;
            j++;
        }
        else
        {
            if(j)
            {
                j = next[j - 1];
            }
            else
            {
                next[i] = 0;
                i++;
            }
        }
    }
    return next;
}


long long String::find(const String& s) const
{
    return find(s._str);
}


std::vector<String> String::split(const char c) const
{
    std::vector<String> vec;

    vec = split(String(1, c));
    return vec;
}


std::vector<String> String::split(const char* s) const
{
    auto str = new char[_length + 1];
    auto part = new char[_length + 1];
    std::vector<String> vec;

    strncpy_s(str, _length + 1, _str, _length + 1);


    auto _s = String(str);
    long long index = -1;
    bool flag = false;
    while(true)
    {
        index = _s.find(s);
        if(index > -1)
        {
            flag = true;
            strncpy_s(part, _length + 1, str, index);
            vec.push_back(String(part));
            memmove_s(str, _length + 1, str + index + strlen(s), _length + 1 - index - strlen(s));
            _s = String(str);
        }
        else
        {
            if(!flag)
                break;
            else
                vec.push_back(String(str));
            break;
        }
    }

    delete[] str;
    delete[] part;
    return vec;
}


std::vector<String> String::split(const String& s) const
{
    auto vec = split(s._str);
    return vec;
}


String String::cut(const size_t begin, const size_t end) const
{
    auto str = new char[end - begin + 1]{'\0'};
    strncpy_s(str, end - begin + 1, _str + begin, end - begin);
    auto _ =  String(str);
    delete[] str;
    return _;
}


String String::join(const std::vector<String>& vec) const
{
    String _s;
    for(auto i = 0; i < vec.size(); i++)
    {
        _s = _s + vec[i];
        if(i + 1 == vec.size())
            break;
        _s = _s + *this;
    }
    return _s;
}


String String::replace(const String& s1, const String& s2) const
{
    auto vec = split(s1);
    String s;
    for(auto i = vec.begin(); i != vec.end(); i++)
    {
        s = i + 1 != vec.end() ? s + *i + s2 : s + *i;
    }
    return s;
}


String String::lower() const
{
    auto str = new char[_length + 1];
    strcpy_s(str, _length + 1, _str);
    for(size_t i = 0; i < _length; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return String(str);
}


String String::upper() const
{
    auto str = new char[_length + 1];
    strcpy_s(str, _length + 1, _str);
    for(size_t i = 0; i < _length; i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return String(str);
}



String String::capitalize() const
{
    if(_str[0] >= 'a' && _str[0] <= 'z')
    {
        auto str = new char[_length + 1];
        strcpy_s(str, _length + 1, _str);
        str[0] -= 32;
        return String(str);
    }
    else
    {
        return *this;
    }
}


template<class T>
T to_integer(const String& s)
{
    unsigned int w = 1;
    T num = 0;

    for(auto c = s._data() + s.length() - 1; c != s._data() - 1; c--)
    {
        switch(*c)
        {
            case '0': break;
            case '1': num += w; break;
            case '2': num += w * 2; break;
            case '3': num += w * 3; break;
            case '4': num += w * 4; break;
            case '5': num += w * 5; break;
            case '6': num += w * 6; break;
            case '7': num += w * 7; break;
            case '8': num += w * 8; break;
            case '9': num += w * 9; break;
            case '-':
            {
                if(c == s._data())
                    num = 0 - num;
                else
                    exit(1);
            }
            break;
            default: std::cout << "unexpected char" << std::endl; exit(1);
        }
        w *= 10;
    }
    return num;
}


int String::toint() const
{   
    return to_integer<int>(*this);
}


long String::tolong() const
{
    return to_integer<long>(*this);
}


long long String::tolonglong() const
{
    return to_integer<long long>(*this);
}


unsigned int String::touint() const
{
    return to_integer<unsigned int>(*this);
}


unsigned long String::toulong() const
{
    return to_integer<unsigned long>(*this);
}


unsigned long long String::toulonglong() const
{
    return to_integer<unsigned long long>(*this);
}


String istring::operator+(const char* s1, const String& s2)
{
    auto _s = String(s1);
    return s2 + _s;
}


std::ostream& istring::operator<<(std::ostream& out, const String& s)
{
    out << s._str;
    return out;
}


std::istream& istring::operator>>(std::istream& in, String& s)
{
    char _s[256] = {0};
    in >> _s;
    s._length = strlen(_s);

    if(!s._str)
        s._str = new char[strlen(_s) + 1];
    else
    {
        delete[] s._str;
        s._str = new char[strlen(_s) + 1];
    }
    strcpy_s(s._str, s._length + 1, _s);

    return in;
}
