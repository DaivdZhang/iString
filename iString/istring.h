#ifndef ISTRING_H_
#define ISTRING_H_

#include <iostream>
#include <vector>

namespace istring
{
    class String
    {
        friend std::ostream& operator<<(std::ostream&, const String&);
        friend std::istream& operator>>(std::istream&, String&);

    private:
        size_t _length = 0;
        char* _str = nullptr;

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
        String operator+(const String&) const;
        String operator*(const size_t) const;

        size_t length() const;
        char* _data() const;
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

    String operator+(const char*, const String&);
    std::ostream& operator<<(std::ostream&, const String&);
    std::istream& operator>>(std::istream&, String&);
}

#endif
