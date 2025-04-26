#include "mystringlib.h"
#include <ostream>
#include <stdexcept>

char *String::data_ptr() {
    return on_heap ? storage.heap.get() : storage.sso;
}

const char *String::data_ptr() const {
    return on_heap ? storage.heap.get() : storage.sso;
}

std::ostream &operator<<(std::ostream &os, const String &str) {
    return os << str.c_str();
}

size_t String::size() const {
    return length;
}

const char *String::c_str() const {
    return data_ptr();
}

String::~String() {
    if (on_heap) {
        storage.heap.~unique_ptr<char[]>();
    }
}

String::String() {
    storage.sso[0] = '\0';
}

String::String(const char *str) {
    length = std::strlen(str);
    if (length < SSO_SIZE) {
        on_heap = false;
    }
    else {
        on_heap = true;
        new (&storage.heap) std::unique_ptr<char[]>(std::make_unique<char[]>(length + 1));
    }
    memcpy(data_ptr(), str, length + 1);
}

String::String(const String &other) {
    strcpy(*this, other);
}

String &String::operator=(const String &other) {
    if (this != &other) {
        if (on_heap) {
            storage.heap.~unique_ptr<char[]>();
        }
        length = other.length;
        on_heap = other.on_heap;
        if (on_heap) {
            new (&storage.heap) std::unique_ptr<char[]>(std::make_unique<char[]>(length + 1));
        }
        memcpy(data_ptr(), other.data_ptr(), length + 1);
    }
    return *this;
}

char &String::operator[](size_t index) {
    if (index >= length) {
        throw std::out_of_range("out of range");
    }
    return data_ptr()[index];
}

String::iterator String::begin() {
    return data_ptr();
}

String::iterator String::end() {
    return data_ptr() + length;
}

String::const_iterator String::cbegin() const {
    return data_ptr();
}

String::const_iterator String::cend() const {
    return data_ptr() + length;
}

size_t String::strlen(const String &s) {
    return s.size();
}

int String::strcmp(const String &s1, const String &s2) {
    const_iterator i1 = s1.cbegin(), i2 = s2.cbegin();
    while (i1 != s1.cend() && i2 != s2.cend() && *i1 == *i2) {
        i1++;
        i2++;
    }
    return *i1 - *i2;
}

bool String::operator==(const String &other) const {
    return strcmp(*this, other) == 0;
}

bool String::operator!=(const String &other) const {
    return strcmp(*this, other) != 0;
}

bool String::operator<(const String &other) const {
    return strcmp(*this, other) < 0;
}

bool String::operator>(const String &other) const {
    return strcmp(*this, other) > 0;
}

void *String::memcpy(void *s1, const void *s2, size_t n) {
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }
    char *dest = static_cast<char*>(s1);
    const char *src = static_cast<const char*>(s2);
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    return s1;
}

void String::strcpy(String &s1, const String &s2) {
    s1.length = s2.length;
    s1.on_heap = s2.on_heap;
    if (s1.on_heap) {
        new (&s1.storage.heap) std::unique_ptr<char[]>(std::make_unique<char[]>(s1.length + 1));
    }
    memcpy(s1.data_ptr(), s2.data_ptr(), s1.length + 1);
}

void String::strncpy(String &s1, const String &s2, size_t n) {
    s1.length = std::min(n, s2.length);
    s1.on_heap = std::min(n, s2.length) < SSO_SIZE;
    if (s1.on_heap) {
        new (&s1.storage.heap) std::unique_ptr<char[]>(std::make_unique<char[]>(s1.length + 1));
    }
    memcpy(s1.data_ptr(), s2.data_ptr(), s1.length + 1);
}

void *String::memmove(void *s1, const void *s2, size_t n) {
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }
    char *dest = static_cast<char*>(s1);
    const char *src = static_cast<const char*>(s2);
    if (dest <= src || dest >= src + n) {
        for (size_t i = 0; i < n; ++i) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i = n; i > 0; --i) {
            dest[i - 1] = src[i - 1];
        }
    }
    return s1;
}

String* String::strerror(int errnum) {
    String errorMessages[] = {
        String("No error"),
        String("Permission denied"),
        String("File not found"),
        String("Invalid argument")
    };
    return &errorMessages[errnum];
}

char *String::strcat(char *s1, const char *s2) {
    size_t i = 0, j = 0;
    while (s1[i] != '\0') {
        ++i;
    }
    while (s2[j] != '\0') {
        s1[i] = s2[j];
        ++i;
        ++j;
    }
    s1[i] = '\0';
    return s1;
}

String &String::operator+=(const String &other) {
    size_t new_size = length + other.size();
    if (new_size < SSO_SIZE) {
        strcat(data_ptr(), other.data_ptr());
    }
    else {
        on_heap = true;
        auto new_data = std::unique_ptr<char[]>(std::make_unique<char[]>(new_size + 1));
        String buf(*this);
        storage.heap = std::move(new_data);
        strcpy(*this, buf);
        strcat(data_ptr(), other.data_ptr());
    }
    length = new_size;
    return *this;
}

String &String::operator+=(const char *str) {
    *this += String(str);
    return *this;
}

void String::push_back(char c) {
    *this += String(&c);
}

int String::strncmp(const String &s1, const String &s2, size_t n) {
    const_iterator i1 = s1.cbegin(), i2 = s2.cbegin();
    while (i1 - s1.cbegin() < n && i1 != s1.cend() && i2 != s2.cend() && *i1 == *i2) {
        i1++;
        i2++;
    }
    return *i1 - *i2;
}

char *String::strchr(String &str, int c) {
    for (iterator it = str.begin(); it != str.end(); ++it) {
        if (*it == c) {
            return it;
        }
    }
    return nullptr;
}

void *String::memset(void *s, int c, size_t n) {
    size_t i;
    char *ss = (char*) s;
    for (i = 0; i < n; i++) {
        ss[i] = (char)c;
    }
    return s;
}
