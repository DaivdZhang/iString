#ifndef ISTRING_H_
#define ISTRING_H_

#include <iostream>
#include <vector>

#define CHECK_MEM_ALLOC(ptr) do{\
                                if(!ptr){\
                                    std::cerr << "String object at " << this << std::endl;\
                                    std::cerr << "function: " << __FUNCTION__ << std::endl;\
                                    std::cerr << "Failed to allocate memory!"<< std::endl;\
                                    std::cerr << "file: " << __FILE__ <<', ';\
                                    std::cerr << "line: " << __LINE__ << std::endl;\
                                }\
                             }while(0);


namespace istring
{
    class String
    {
        friend std::ostream& operator<<(std::ostream&, const String&);
        friend std::istream& operator>>(std::istream&, String&);
        friend String operator+(const String&, const String&);

    private:
        size_t _length = 0;
        char* _str = nullptr;

        template<class T>
        T to_integer() const
        {
            T w = 1;
            T num = 0;

            for(auto c = this->_str + this->_length - 1; c != this->_str - 1; c--)
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
                        if(c == this->_str)
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

        template<class T>
        T to_float() const
        {
            auto vec = this->split('.');
            if(vec.size() == 0)
                return this->to_integer<T>();
            else if(vec.size() != 2)
                exit(1);

            auto a = vec[0].to_integer<T>();
            T b = 0;
            T w = vec[0][0] != '-' ? static_cast<T>(0.1) : static_cast<T>(-0.1);

            for(auto c = vec[1]._str; c != vec[1]._str + vec[1]._length; c++)
            {
                switch(*c)
                {
                    case '0': break;
                    case '1': b += w; break;
                    case '2': b += w * 2; break;
                    case '3': b += w * 3; break;
                    case '4': b += w * 4; break;
                    case '5': b += w * 5; break;
                    case '6': b += w * 6; break;
                    case '7': b += w * 7; break;
                    case '8': b += w * 8; break;
                    case '9': b += w * 9; break;
                    default: std::cout << "unexpected char" << std::endl; exit(1);
                }
                w *= static_cast<T>(0.1);
            }
            return a + b;
        }

    public:
        String();
        String(const char);
        String(const char*);
        String(const String&);
        String(String&&);
        String(size_t, const char);
        String(size_t, const char*);
        ~String();

        String& operator=(const String&);
        String& operator=(String&&);
        bool operator==(const String&) const;
        bool operator!=(const String&) const;
        const char& operator[](size_t i) const;
        String operator*(const size_t) const;
        String& operator+=(const String&);

        size_t length() const;
        const char* c_str() const;
        bool empty() const;

        long long find(const char) const;
        long long find(const char*) const;
        long long find(const String&) const;

        std::vector<String> split(const char) const;
        std::vector<String> split(const char*) const;
        std::vector<String> split(const String&) const;

        String cut(const size_t, const size_t) const;

        String join(const std::vector<String>&) const;

        String replace(const String&, const String&) const;
        String lower() const;
        String upper() const;
        String capitalize() const;

        int toint() const;
        long tolong() const;
        long long tolonglong() const;
        unsigned int touint() const;
        unsigned long toulong() const;
        unsigned long long toulonglong() const;
        float tofloat() const;
        double todouble() const;
    };

    String operator+(const String&, const String&);
    std::ostream& operator<<(std::ostream&, const String&);
    std::istream& operator>>(std::istream&, String&);
}

#endif
