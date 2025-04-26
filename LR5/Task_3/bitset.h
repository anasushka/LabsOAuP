#ifndef BITSET_H
#define BITSET_H

#include <QString>

class BitSet
{
public:
    //constructors
    explicit BitSet(int);
    ~BitSet();
    //functions
    bool test(int) const;
    int size() const;
    void set(int position);
    void set();
    void reset(int position);
    void reset();
    void flip(int position);
    void flip();
    bool all() const;
    bool any() const;
    bool none() const;
    int count() const;
    QString to_string() const;
    unsigned long long to_ullong() const;
    unsigned long to_ulong() const;
    //operators
    bool operator[](int) const;
    bool &operator[](int);
    BitSet operator~() const;
    BitSet operator&(const BitSet& other) const;
    BitSet operator|(const BitSet& other) const;

private:
    static const int cnt_bits = 16;
    static const int size_of_block = sizeof(unsigned short) * cnt_bits;

    unsigned short* blockData;
    int totalBits;
};


#endif // BITSET_H
