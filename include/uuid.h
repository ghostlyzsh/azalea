#pragma once

class UUID {
public:
    UUID(long long higher, long long lower);

    long long higher;
    long long lower;
};
