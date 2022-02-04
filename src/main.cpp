#include <iostream>
#include <memory>
#include <sndfile.hh>

#include "envelope.hpp"
#include "osc.hpp"
#include "static_osc_bank.hpp"
#include "stream_interface.hpp"

const unsigned int StreamInterface::s_sampleRate = 44100;
int main() {
    std::vector<double> relAmps {1.0, 1/2.0, 1/3.0, 1/4.0};
    std::vector<double> relFreqs {1, 2, 3, 4};
    std::shared_ptr<StaticOscBank> osc = std::make_shared<StaticOscBank>(
        4,
        relAmps,
        relFreqs
    );
    osc->updateFreq(440);

    std::shared_ptr<Envelope> freqEnv = std::make_shared<Envelope>();
    freqEnv->addBreakpoint(0, 40);
    freqEnv->addBreakpoint(0.5, 880);
    freqEnv->addBreakpoint(1, 1000);

    std::shared_ptr<Envelope> ampEnv = std::make_shared<Envelope>();
    ampEnv->addBreakpoint(0,1);
    ampEnv->addBreakpoint(1,0);

    SndfileHandle file;
    int channels = 1;
    std::string fileName = "sine.wav";
    const int format = SF_FORMAT_WAV | SF_FORMAT_DOUBLE;
    file = SndfileHandle(fileName, SFM_WRITE, format, channels, StreamInterface::s_sampleRate);
    
    double buf[StreamInterface::s_sampleRate];
    for(int i=0; i<StreamInterface::s_sampleRate; ++i) {
        buf[i] = ampEnv->next() * osc->next();
        osc->updateFreq(freqEnv->next());
    }
    file.write(buf, StreamInterface::s_sampleRate);

    return 0;
}
