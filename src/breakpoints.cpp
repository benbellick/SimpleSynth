#include "breakpoints.hpp"

Breakpoints::Breakpoints(unsigned int sampleRate) :
    StreamInterface(sampleRate), 
    m_breakpoints(),
    m_currentLocation(m_breakpoints.cbegin()) {}

size_t Breakpoints::size() const {
    return m_breakpoints.size();
}

//TODO maybe change this to bool to see if there was an error?
void Breakpoints::addBreakpoint(double time, double value) {
    /*
     * Retaining a sorting invariant here: all entires into Breakpoints must comply with following conditions:
     * 1) Sorted by time
     * 2) no common time values
     */
    Breakpoint bkpt {time, value};
    if(!m_breakpoints.size()) {
        m_breakpoints.push_back(bkpt);
        return;
    }
    auto timeComp = [] (const Breakpoint& lhs, const Breakpoint& rhs) {return lhs.time < rhs.time;};
    auto candidateLocation = std::upper_bound(m_breakpoints.begin(), m_breakpoints.end(), bkpt, timeComp);
    if(candidateLocation->time == bkpt.time)
        return; //TODO maybe throw something here
    m_breakpoints.insert(candidateLocation, bkpt);
    return;
}

double Breakpoints::next() {
    //TODO: implement
    return -1000000;
}
void Breakpoints::reset() {
    //TODO: implement
}

std::vector<double> Breakpoints::getTimes() const {
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
