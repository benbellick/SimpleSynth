#include "mono_synth.hpp"

MonoSynth::MonoSynth(
    std::shared_ptr<Osc> osc,
    std::shared_ptr<StreamInterface> ampEnvelope,
    std::shared_ptr<StreamInterface> freqEnvelope
) :
    m_osc(osc),
    m_ampEnvelope(ampEnvelope),
    m_freqEnvelope(freqEnvelope) {}

double MonoSynth::next() {
    m_osc->updateFreq(m_freqEnvelope->next());
    return m_ampEnvelope->next() * m_osc->next();
}

void MonoSynth::next(Buffer<double>& buffer) {
    //TODO: improve?
    for(size_t i=0; i<buffer.size(); ++i)
        buffer[i]=next();
}

void MonoSynth::reset() {
    m_osc->reset();
    m_ampEnvelope->reset();
    m_freqEnvelope->reset();
}
