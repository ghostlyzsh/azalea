#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include "zlib.h"

class ZlibHandler {
public:
    static std::string compress(const std::string &data, int compressionlevel);

    static std::string decompress(const std::string &data);
};
