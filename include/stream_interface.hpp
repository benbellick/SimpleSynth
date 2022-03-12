#pragma once
#include "buffer.hpp"

class StreamInterface {
    public:
        virtual ~StreamInterface() {};
        virtual double next() = 0;
        virtual void next(Buffer<double>& buffer) = 0;
        virtual void reset() = 0;
    public:
        static const unsigned int s_sampleRate;
};
