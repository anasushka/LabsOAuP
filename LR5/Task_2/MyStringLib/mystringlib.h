#pragma once
#ifndef MYSTRINGLIB_H
#define MYSTRINGLIB_H

#include "MyStringLib_global.h"
#include <memory>
#include <cstring>

class MYSTRINGLIB_EXPORT String
{
private:
    static const size_t SSO_SIZE = 16;

    union Storage {
        char sso[SSO_SIZE] = {};
        std::unique_ptr<char[]> heap;

        Storage() {}
        ~Storage() {}
    } storage;

    size_t length = 0;
    bool on_heap = false;

    char* data_ptr();
    const char* data_ptr() const;

public:
    String();
    explicit String(const char* str);
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    const char* c_str() const;
    size_t size() const;

    friend std::ostream& operator<<(std::ostream& os, const String& str);

    char& operator[](size_t index);

    typedef char *iterator;
    typedef const char *const_iterator;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    String &operator+=(const String &other);
    String &operator+=(const char *str);

    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    bool operator<(const String &other) const;
    bool operator>(const String &other) const;

    void push_back(char c);
    static void *memcpy(void *s1, const void *s2, size_t n);
    static void *memmove(void *s1, const void *s2, size_t n);
    static void strcpy(String& s1, const String& s2);
    static void strncpy(String& s1, const String& s2, size_t n);
    static char *strcat(char *s1, const char *s2);
    static int strcmp(const String& s1, const String& s2);
    static int strncmp(const String& s1, const String& s2, size_t n);
    static void *memset(void *s, int c, size_t n);
    static String* strerror(int errnum);
    static size_t strlen(const String &s);
    static char* strchr(String& str, int c);
};

#endif // MYSTRINGLIB_H
