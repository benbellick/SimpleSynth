#include "constant_stream.hpp"

ConstantStream::ConstantStream(const double value) :
    m_value(value) {}

double ConstantStream::next() {
    return m_value;
}

void ConstantStream::reset(){}
