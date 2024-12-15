#include "hasher.h"

#include <string>

Hasher::Hasher(const std::string& s)
{
    long p1_pow = p1, p2_pow = p2;
    for (char ch: s) {
        hash1 = (hash1 + (ch + 1) * p1_pow) % m1;
        hash2 = (hash2 + (ch + 1) * p2_pow) % m2;

        p1_pow = (p1_pow * p1) % m1;
        p2_pow = (p2_pow * p2) % m2;
    }
}

bool Hasher::operator==(const Hasher& other)
{
    return (hash1 == other.hash1 && hash2 == other.hash2);
}