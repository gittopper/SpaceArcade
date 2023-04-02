#pragma once

#include <assert.h>

#include <cmath>
#include <exception>
#include <iostream>
#include <logger.hpp>
#include <vector>

struct PuzzleException : public std::logic_error {
    PuzzleException(const std::string& what) : std::logic_error(what.c_str()) {}
};

#define FLOAT_EPS 0.0001

//#define BREAK_ON_LINE(x) if (!(x)) { throw PuzzleException(std::string("error
//at file ") + __FILE__ + " at line " + std::to_string(__LINE__));} #define
// BREAK_ON_LINE(x) assert(x);
#define BREAK_ON_LINE(x)
#define m_STDCALL_SUPPORTED
