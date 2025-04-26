#include "bitset.h"


BitSet::BitSet(int size): totalBits(size)
{
    int arrSize = (cnt_bits + size - 1) / cnt_bits;
    blockData = new unsigned short[arrSize];
    for (int i = 0; i < arrSize; ++i)
    {
        blockData[i] = 0;
    }
}

BitSet::~BitSet()
{
    delete[] blockData;
}

bool BitSet::test(int pos) const {
    return (pos >= 0 && pos < totalBits) && (blockData[pos / cnt_bits] & (1 << (pos % cnt_bits)));
}

int BitSet::size() const
{
    return totalBits;
}

void BitSet::set(int position) {
    if (position >= 0 && position < totalBits) {
        int blockIndex = position / cnt_bits;
        int bitOffset = position % cnt_bits;
        unsigned short mask = (1 << bitOffset);
        blockData[blockIndex] |= mask;
    }
}

void BitSet::set() {
    for (int i = 0; i < totalBits; ++i) {
        int blockIndex = i / cnt_bits;
        int bitOffset = i % cnt_bits;
        unsigned short mask = (1 << bitOffset);
        blockData[blockIndex] |= mask;
    }
}

void BitSet::reset(int pos) {
    if (pos >= 0 && pos < totalBits) {
        int blockIndex = pos / cnt_bits;
        int bitOffset = pos % cnt_bits;
        unsigned short mask = ~(1 << bitOffset);
        blockData[blockIndex] &= mask;
    }
}

void BitSet::reset() {
    for (int i = 0; i < totalBits; ++i) {
        int blockIndex = i / cnt_bits;
        int bitOffset = i % cnt_bits;
        unsigned short mask = ~(1 << bitOffset);
        blockData[blockIndex] &= mask;
    }
}

void BitSet::flip(int pos) {
    if (pos >= 0 && pos < totalBits) {
        int blockIndex = pos / cnt_bits;
        int bitOffset = pos % cnt_bits;
        unsigned short mask = (1 << bitOffset);
        blockData[blockIndex] ^= mask;
    }
}

void BitSet::flip() {
    for (int i = 0; i < totalBits; ++i) {
        int blockIndex = i / cnt_bits;
        int bitOffset = i % cnt_bits;
        unsigned short mask = (1 << bitOffset);
        blockData[blockIndex] ^= mask;
    }
}

bool BitSet::all() const {
    int fullSizedBlocks = totalBits / cnt_bits;
    int partialSizedBlock = totalBits % cnt_bits;
    unsigned short fullBlockMask = (1 << cnt_bits) - 1;
    unsigned short partialBlockMask = (1 << partialSizedBlock) - 1;

    for (int i = 0; i < fullSizedBlocks; ++i) {
        if (blockData[i] != fullBlockMask) {
            return false;
        }
    }

    if (partialSizedBlock > 0 && blockData[fullSizedBlocks] != partialBlockMask) {
        return false;
    }

    return true;
}

bool BitSet::any() const {
    int totalBlocks = (totalBits + cnt_bits - 1) / cnt_bits;
    for (int i = 0; i < totalBlocks; ++i) {
        if (blockData[i] != 0) {
            return true;
        }
    }
    return false;
}

bool BitSet::none() const
{
    return !any();
}

int BitSet::count() const {
    int count = 0;
    int totalBlocks = (totalBits + cnt_bits - 1) / cnt_bits;
    for (int i = 0; i < totalBlocks; ++i) {
        unsigned short value = blockData[i];
        while (value) {
            count += (value & 1);
            value >>= 1;
        }
    }
    return count;
}

QString BitSet::to_string() const {
    QString str;
    for (int i = totalBits - 1; i >= 0; --i) {
        if (test(i)) {
            str += '1';
        } else {
            str += '0';
        }
    }
    return str;
}

unsigned long BitSet::to_ulong() const {
    unsigned long value = 0;
    for (int i = totalBits - 1; i >= 0; --i) {
        if (test(i)) {
            value |= (1UL << i);
        }
    }
    return value;
}

unsigned long long BitSet::to_ullong() const {
    unsigned long long value = 0;
    for (int i = totalBits - 1; i >= 0; --i) {
        if (test(i)) {
            value |= (1ULL << i);
        }
    }
    return value;
}

bool BitSet::operator[](int pos) const
{
    return test(pos);
}

bool& BitSet::operator[](int pos) {
    static bool dummy;
    if (pos < 0 || pos >= totalBits) {
        return dummy;
    }
    return reinterpret_cast<bool&>(blockData[pos / cnt_bits] |= (1 << (pos % cnt_bits)));
}

BitSet BitSet::operator~() const {
    BitSet result(totalBits);
    int blockCount = (totalBits + cnt_bits - 1) / cnt_bits;
    for (int i = 0; i < blockCount; ++i) {
        result.blockData[i] = ~blockData[i];
    }
    return result;
}

BitSet BitSet::operator&(const BitSet& other) const {
    BitSet result(totalBits);
    int blockCount = (totalBits + cnt_bits - 1) / cnt_bits;
    for (int i = 0; i < blockCount; ++i) {
        result.blockData[i] = blockData[i] & other.blockData[i];
    }
    return result;
}

BitSet BitSet::operator|(const BitSet& other) const {
    BitSet result(totalBits);
    int blockCount = (totalBits + cnt_bits - 1) / cnt_bits;
    for (int i = 0; i < blockCount; ++i) {
        result.blockData[i] = blockData[i] | other.blockData[i];
    }
    return result;
}
