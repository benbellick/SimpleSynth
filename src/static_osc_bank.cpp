#include <memory>
#include <numeric>

#include "static_osc_bank.hpp"
#include "sin_osc.hpp"

StaticOscBank::StaticOscBank(
    const unsigned int numOfOscs,
    const std::vector<double>& relativeAmps,
    const std::vector<double>& relativeFreqs,
    const double lowCutFreq,
    const double highCutFreq
) :
    Osc(),
    m_numOfOscs(numOfOscs),
    m_relativeAmps(relativeAmps),
    m_relativeFreqs(relativeFreqs),
    m_oscs(m_numOfOscs),
    m_lowCutFreq(lowCutFreq),
    m_highCutFreq(highCutFreq){
    //TODO: Throw if there is a number mismatch between all of the sizes
    for(unsigned int i=0; i<numOfOscs; ++i) {
        m_oscs.at(i) = std::make_unique<SinOsc>();
    }
}

StaticOscBank::StaticOscBank(
    const unsigned int numOfOscs,
    const std::vector<double>& relativeAmps,
    const std::vector<double>& relativeFreqs,
    const std::shared_ptr<const std::vector<double>> lookupTable,
    const Enums::InterpType interpType,
    const double lowCutFreq,
    const double highCutFreq
) :
    Osc(),
    m_numOfOscs(numOfOscs),
    m_relativeAmps(relativeAmps),
    m_relativeFreqs(relativeFreqs),
    m_oscs(m_numOfOscs),
    m_lowCutFreq(lowCutFreq),
    m_highCutFreq(highCutFreq){
    //TODO: Throw if there is a number mismatch between all of the sizes
    for(unsigned int i=0; i<numOfOscs; ++i) {
        m_oscs.at(i) = std::make_unique<LookupOsc>(
            lookupTable,
            interpType
        );
    }
}

double StaticOscBank::next() {
    //TODO: make this into transform_reduce call?
    std::vector<double> vals(m_oscs.size());
    std::transform(
        m_oscs.begin(),
        m_oscs.end(),
        vals.begin(),
        [idx=0, this](std::unique_ptr<Osc>& osc) mutable -> double {
            double curFreq = osc->getFreq();
            double val = m_relativeAmps.at(idx++) * osc->next();
            return m_lowCutFreq <= curFreq && curFreq <= m_highCutFreq ?
                val : 0;
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

void StaticOscBank::next(Buffer<double>& buffer) {
    //TODO: Also consider if this implementation is optimal
    for(size_t i=0; i<buffer.size(); ++i)
        buffer[i]=next();
}

void StaticOscBank::reset() {
    std::for_each(
        m_oscs.begin(), 
        m_oscs.end(), 
        [](std::unique_ptr<Osc>& osc) {osc->reset();}
    );
}

double StaticOscBank::getFreq() const {
    return m_curFreq;
}

void StaticOscBank::updateFreq(double freq){
    m_curFreq = freq;
    std::for_each(
        m_oscs.begin(),
        m_oscs.end(),
        [idx=0, this](std::unique_ptr<Osc>& osc) mutable {
            osc->updateFreq(m_relativeFreqs.at(idx++) * m_curFreq);
        }
    );
}
