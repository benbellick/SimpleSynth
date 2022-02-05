#pragma once
#include "stream_interface.hpp"

//For now, we assume sin, we will alter later
class Osc : public StreamInterface {
    public:
        Osc();
        const double getFreq() const;
        void updateFreq(double freq);
        double next() override;
        void reset() override;
    private:
        void boundCurPhase();
        double m_curFreq;
        double m_curPhase;
        double m_incr;
};
