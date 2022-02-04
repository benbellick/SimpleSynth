#include <math.h>

#include "osc.hpp"

Osc::Osc() :
    StreamInterface(),
    m_curFreq(0.0),
    m_curPhase(0.0),
    m_incr(0){
    }

const double Osc::getFreq() const {
    return m_curFreq;
}
void Osc::updateFreq(double freq) {
    m_curFreq = freq;
    m_incr = m_curFreq * 2 * M_PI / s_sampleRate;
}

double Osc::next(){
    //TODO: throw if freq is 0?
    //std::cout << "curphase: " << m_curPhase << ",\t" << "curinc: " << m_incr << ",\t" << "curfreq: " << m_curFreq << std::endl;
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
