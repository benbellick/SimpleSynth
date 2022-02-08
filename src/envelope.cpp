#include "envelope.hpp"

Envelope::Envelope(
    Enums::InterpType interpType
) :
    StreamInterface(), 
    m_interpType(interpType),
    m_breakpoints(),
    m_curTime(0.0),
    m_currentLocation(m_breakpoints.cbegin()) {}

size_t Envelope::size() const {
    return m_breakpoints.size();
}

//TODO maybe change this to bool to see if there was an error?
//Note that adding breakpoints will always reset iterator for now
void Envelope::addBreakpoint(double time, double value) {
    /*
     * Retaining a sorting invariant here: all entires into Envelope must comply with following conditions:
     * 1) Sorted by time
     * 2) no common time values
     */
    Breakpoint bkpt {time, value};
    if(!m_breakpoints.size()) {
        m_breakpoints.push_back(bkpt);
        reset();
        return;
    }
    auto timeComp = [] (const Breakpoint& lhs, const Breakpoint& rhs) {return lhs.time < rhs.time;};
    auto candidateLocation = std::upper_bound(m_breakpoints.begin(), m_breakpoints.end(), bkpt, timeComp);
    if(candidateLocation->time == bkpt.time)
        return; //TODO maybe throw something here
    m_breakpoints.insert(candidateLocation, bkpt);
    reset();
    return;
}

double Envelope::next() {
    switch(m_interpType){
    case(Enums::InterpType::Truncate):
        //TODO throw
        return -2;
    case(Enums::InterpType::Linear):
        if((m_curTime == m_currentLocation->time) ||
           (m_curTime >= m_currentLocation->time
            && (m_currentLocation+1) == m_breakpoints.cend())){
            m_curTime += 1.0 / s_sampleRate;
            return m_currentLocation->value;
        } 
        else if(m_curTime >= m_currentLocation->time){
            const Breakpoint& curBrkpt = *m_currentLocation;
            const Breakpoint& nextBrkpt = *(m_currentLocation+1);
            double slope = (nextBrkpt.value - curBrkpt.value) / 
                                (nextBrkpt.time - curBrkpt.time);
            double interpValue = curBrkpt.value + slope * (m_curTime - curBrkpt.time);
            m_curTime+= 1.0 / s_sampleRate;
            if(m_curTime >= (m_currentLocation+1)->time)
                m_currentLocation++;
            return interpValue;
        } else if(m_curTime <= m_currentLocation->time){
            return -1;
        }
        break;
    }
    //throw an error here (bad state: curTime is before curLoc's time
    return -1;
}
void Envelope::reset() {
    m_curTime = 0;
    m_currentLocation = m_breakpoints.cbegin();
}

std::vector<double> Envelope::getTimes() const {
    std::vector<double> times;
    std::for_each(
        m_breakpoints.cbegin(), 
        m_breakpoints.cend(), 
        [&times](const Breakpoint& bkpt) mutable {
            times.push_back(bkpt.time);
        }
    );
    return times;
}
