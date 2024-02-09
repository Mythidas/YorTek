#pragma once

#include <bitset>

const size_t MAX_ENTITIES = 1000;
const size_t MAX_COMPONENTS = 32;

using ComponentMask = std::bitset<MAX_COMPONENTS>;