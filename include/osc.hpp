#pragma once
#include "stream_interface.hpp"

//For now, we assume sin, we will alter later
class Osc : public StreamInterface<double> {
    public:
        Osc(unsigned long srate);
        void updateFreq(double freq);
        double next() override;
        void reset() override;
    private:
        void boundCurPhase();
        double m_sampleRate;
        double m_curFreq;
        double m_curPhase;
        double m_incr;
};
