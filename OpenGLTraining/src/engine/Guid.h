#pragma once
#include <iostream>
#include <random>
#include <sstream>

class Guid
{
private:
    uint64_t part1;
    uint64_t part2;

public:
    inline const uint64_t Part1() const { return part1; }
    inline const uint64_t Part2() const { return part2; }

    Guid()
    {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;

        part1 = dis(gen);
        part2 = dis(gen);
    }

    std::string toString() const
    {
        std::ostringstream oss;
        oss << std::hex << part1 << '-' << part2;
        return oss.str();
    }

    bool operator==(const Guid& other) const
    {
        return part1 == other.part1 && part2 == other.part2;
    }
};

struct GUIDHash
{
    std::size_t operator()(const Guid& guid) const
    {
        std::size_t seed = 0;
        hash_combine(seed, guid.Part1());
        hash_combine(seed, guid.Part2());
        return seed;
    }

private:

    template <typename T>
    void hash_combine(std::size_t& seed, const T& v) const
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};