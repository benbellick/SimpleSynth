#include <math.h>

#include "sin_osc.hpp"

SinOsc::SinOsc() :
    Osc(){}

double SinOsc::getFreq() const {
    return m_curFreq;
}
void SinOsc::updateFreq(double freq) {
    m_curFreq = freq;
    m_incr = m_curFreq * 2 * M_PI / s_sampleRate;
}

double SinOsc::next(){
    //TODO: throw if freq is 0?
    double tickVal = sin(m_curPhase);
    m_curPhase += m_incr;
    boundCurPhase();
    return tickVal;
}

void SinOsc::reset(){
    m_curPhase = 0.0;
}

void SinOsc::boundCurPhase() {
    if(m_curPhase >= 2 * M_PI)
        m_curPhase -= 2* M_PI;
    if(m_curPhase <= 0.0)
        m_curPhase += 2* M_PI;
}
