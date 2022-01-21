#include "osc.hpp"
#include <math.h>

Osc::Osc(unsigned long srate) :
    StreamInterface(srate),
    m_curFreq(0),
    m_curPhase(0),
    m_incr(0){}

void Osc::updateFreq(double freq) {
    m_curFreq = freq;
    m_incr = freq * 2 * M_PI / (float) m_sampleRate;
}

double Osc::next(){
    //TODO: throw if freq is 0?
    double tickVal = sin(m_curPhase);
    m_curPhase += m_incr;
    return tickVal;
}

void Osc::reset(){
    //TODO: implement
}

void Osc::boundCurPhase() {
    if(m_curPhase >= 2 * M_PI)
        m_curPhase -= 2* M_PI;
    if(m_curPhase <= 0.0)
        m_curPhase += 2* M_PI;
}
