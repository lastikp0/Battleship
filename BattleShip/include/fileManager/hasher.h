#ifndef HASHER
#define HASHER

#include <string>

struct Hasher {
    const int p1 = 31, m1 = 1e9 + 7;
    const int p2 = 37, m2 = 1e9 + 9;

    int hash1 = 0, hash2 = 0;

    Hasher(const std::string& s);

    bool operator==(const Hasher& other);
};

#endif