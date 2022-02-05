#pragma once
#include "stream_interface.hpp"

//For now, we assume sin, we will alter later
class Osc : public StreamInterface {
    public:
        Osc():m_curFreq(0.0), m_curPhase(0.0), m_incr(0.0){};
        virtual ~Osc() {};
        virtual double getFreq() const = 0;
        virtual void updateFreq(double freq) = 0;
    protected:
        double m_curFreq;
        double m_curPhase;
        double m_incr;
};
