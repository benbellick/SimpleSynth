#include "constant_stream.hpp"

ConstantStream::ConstantStream(const double value) :
    m_value(value) {}

double ConstantStream::next() {
    return m_value;
}

void ConstantStream::next(Buffer<double>& buffer) {
    for(size_t i=0; i<buffer.size(); ++i)
        buffer[i] = m_value;
}

void ConstantStream::reset(){}
