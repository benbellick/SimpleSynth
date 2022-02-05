#pragma once

class StreamInterface {
    public:
        virtual ~StreamInterface() {};
        virtual double next() = 0;
        virtual void reset() = 0;
    public:
        static const unsigned int s_sampleRate;
};
