#pragma once

template<typename T>
class StreamInterface {
    public:
        StreamInterface(unsigned int sampleRate) : m_sampleRate(sampleRate) {};
        virtual T next() = 0;
        virtual void reset() = 0;
    protected:
        const unsigned int m_sampleRate;
};
