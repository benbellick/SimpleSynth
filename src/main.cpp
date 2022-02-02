#include <iostream>
#include <memory>
#include <sndfile.hh>

#include "osc.hpp"
#include "envelope.hpp"
#include "stream_interface.hpp"

const unsigned int StreamInterface::s_sampleRate = 44100;
int main() {
    std::shared_ptr<Osc> osc = std::make_shared<Osc>();
    osc->updateFreq(440);
    /*
    for(size_t i=0; i<1000; ++i)
        std::cout << i << "\t" << osc->next() << std::endl;
    */

    std::shared_ptr<Envelope> freqEnv = std::make_shared<Envelope>();
    freqEnv->addBreakpoint(0, 40);
    freqEnv->addBreakpoint(0.5, 880);
    freqEnv->addBreakpoint(1, 1000);

    std::shared_ptr<Envelope> ampEnv = std::make_shared<Envelope>();
    ampEnv->addBreakpoint(0,0);
    ampEnv->addBreakpoint(0.2,1);
    ampEnv->addBreakpoint(1,0);

    for(size_t i=0; i<44100; ++i){
        double freq = freqEnv->next();
        osc->updateFreq(freqEnv->next());
        std::cout << osc->next() * ampEnv->next() << std::endl;
    }

    SndfileHandle file;
    int channels = 1;
    std::string fileName = "sine.wav";
    std::cout << sf_version_string() << std::endl;

    file = SndfileHandle(fileName, SFM_WRITE, SF_FORMAT_WAV, channels, StreamInterface::s_sampleRate);

    return 0;
}
