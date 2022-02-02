#include <exception>
#include <execution>
#include <numeric>

#include "osc_bank.hpp"

OscBank::OscBank() :
    StreamInterface(),
    m_oscs() {}

OscBank::OscBank(unsigned int numOfOscs) :
    StreamInterface(),
    m_oscs(numOfOscs) {
    for(unsigned int i=0; i<numOfOscs; ++i)
        m_oscs.push_back(std::make_shared<Osc>());
}

double OscBank::next() {
    //TODO: make this into transform_reduce call?
    std::vector<double> vals(m_oscs.size());
    std::transform(
        m_oscs.begin(),
        m_oscs.end(),
        vals.begin(),
        [](std::shared_ptr<Osc> osc) -> double {return osc->next();}
    );
    return std::reduce(
        vals.begin(),
        vals.end(),
        0.0,
        std::plus<>()
    );
    return 0;
}

void OscBank::reset() {
    std::for_each(
        m_oscs.begin(), 
        m_oscs.end(), 
        [](std::shared_ptr<Osc> osc) {osc->reset();}
    );
}

void OscBank::addOsc(std::shared_ptr<Osc> osc) {
    m_oscs.push_back(osc);
}
