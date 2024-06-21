#include <map>

#pragma once

template <typename T>
struct State
{
    T output;
    std::map<T, T> next;
};
