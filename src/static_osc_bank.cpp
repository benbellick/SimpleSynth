#include <memory>
#include <numeric>

#include "static_osc_bank.hpp"

StaticOscBank::StaticOscBank(
    const unsigned int numOfOscs,
    const std::vector<double>& relativeAmps,
    const std::vector<double>& relativeFreqs
) :
    StreamInterface(),
    m_numOfOscs(numOfOscs),
    m_relativeAmps(relativeAmps),
    m_relativeFreqs(relativeFreqs)
    {
    //TODO: Throw if there is a number mismatch between all of the sizes
    for(unsigned int i=0; i<numOfOscs; ++i) {
        m_oscs.push_back(std::make_shared<Osc>());
    }
}

double StaticOscBank::next() {
    //TODO: make this into transform_reduce call?
    std::vector<double> vals(m_oscs.size());
    std::transform(
        m_oscs.begin(),
        m_oscs.end(),
        vals.begin(),
        [idx=0, this](std::shared_ptr<Osc> osc) mutable -> double {
            return m_relativeAmps.at(idx++) * osc->next();
        }
    );
    return std::reduce(
        vals.begin(),
        vals.end(),
        0.0,
        std::plus<>()
    );
    return 0;
}

void StaticOscBank::reset() {
    std::for_each(
        m_oscs.begin(), 
        m_oscs.end(), 
        [](std::shared_ptr<Osc> osc) {osc->reset();}
    );
}

void StaticOscBank::updateFreq(double freq){
    m_curFreq = freq;
    std::for_each(
        m_oscs.begin(),
        m_oscs.end(),
        [idx=0, this](std::shared_ptr<Osc> osc) mutable {
            osc->updateFreq(m_relativeFreqs.at(idx++) * m_curFreq);
        }
    );
}
