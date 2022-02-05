#include <iostream>
#include <memory>
#include <sndfile.hh>
#include <math.h>

#include "envelope.hpp"
#include "lookup_osc.hpp"
#include "osc.hpp"
#include "static_osc_bank.hpp"
#include "stream_interface.hpp"

const unsigned int StreamInterface::s_sampleRate = 44100;
int main() {
    //osc test
    int numOfOscs = 20;
    std::vector<double> relAmps;
    std::vector<double> relFreqs;
    for(int i=1; i<=numOfOscs;++i)
        relAmps.push_back(1.0/i), relFreqs.push_back(i);
    std::shared_ptr<StaticOscBank> osc = std::make_shared<StaticOscBank>(
        numOfOscs,
        relAmps,
        relFreqs
    );
    osc->updateFreq(440);

    std::shared_ptr<Envelope> freqEnv = std::make_shared<Envelope>();
    freqEnv->addBreakpoint(0, 440);
    freqEnv->addBreakpoint(1, 20000);

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

    std::shared_ptr<std::vector<double>> sinTable = std::make_shared<std::vector<double>>();
    const int tableLength = 100;
    for(int i=0; i<tableLength; ++i)
        sinTable->push_back(sin(2 * M_PI * i / tableLength));
    std::shared_ptr<LookupOsc> sinLkpOsc = std::make_shared<LookupOsc>(
        sinTable,
        LookupOsc::LinearInterp
    );
    //TODO: should def throw if freq is 0
    sinLkpOsc->updateFreq(440);

    SndfileHandle file2;
    std::string fileName2 = "sine_lookup.wav";
    file2 = SndfileHandle(fileName2, SFM_WRITE, format, channels, StreamInterface::s_sampleRate);
    
    double buf2[StreamInterface::s_sampleRate];
    for(int i=0; i<StreamInterface::s_sampleRate; ++i) {
        buf2[i] = sinLkpOsc->next();
    }
    file2.write(buf2, StreamInterface::s_sampleRate);

    return 0;
}
