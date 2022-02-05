#include <iostream>
#include "lookup_osc.hpp"

LookupOsc::LookupOsc(
    std::shared_ptr<const std::vector<double>> lookupTable,
    LookupOsc::InterpType interpType
):
    m_curFreq(0),
    m_curPhase(0),
    m_incr(0),
    m_interpType(interpType),
    m_lookupTable(lookupTable){}

double LookupOsc::getFreq() const {
    return m_curFreq;
}

void LookupOsc::updateFreq(const double freq){
    m_curFreq = freq;
    m_incr = m_curFreq * m_lookupTable->size() / s_sampleRate;
}

double LookupOsc::next() {
    double tickVal(0);
    switch(m_interpType){
    case(Truncate):
        tickVal = m_lookupTable->at((int) m_curPhase);
        break;
    case(LinearInterp):
        int left = (int) m_curPhase;
        int right = left+1;
        double diff = m_curPhase - left;
        //Modulo to handle potential wrap around
        double slope = m_lookupTable->at(right % m_lookupTable->size()) - 
            m_lookupTable->at(left);
        tickVal = m_lookupTable->at(left) + slope * diff;
        break;
    }
    m_curPhase += m_incr;
    boundCurPhase();
    return tickVal;
}

void LookupOsc::reset() {
    m_curPhase = 0.0;
}

void LookupOsc::boundCurPhase() {
    const int tableLength = m_lookupTable->size();
    if(m_curPhase >= tableLength)
        m_curPhase -= tableLength;
    if(m_curPhase <= 0.0)
        m_curPhase += tableLength;
}
