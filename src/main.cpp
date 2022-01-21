#include <iostream>
#include <memory>
#include <sndfile.h>

#include "osc.hpp"
#include "breakpoints.hpp"

int main() {
    std::shared_ptr<Osc> osc = std::make_shared<Osc>(44100);
    osc->updateFreq(440);
    /*
    for(size_t i=0; i<1000; ++i)
        std::cout << i << "\t" << osc->next() << std::endl;
    */

    std::shared_ptr<Breakpoints> brkpts = std::make_shared<Breakpoints>(44100);
    brkpts->addBreakpoint(0.0, 0.0);
    brkpts->addBreakpoint(0.0, 0.0);
    brkpts->addBreakpoint(0.1, 1.0);
    brkpts->addBreakpoint(0.2, 0.5);
    brkpts->addBreakpoint(0.3, 0.3);
    brkpts->addBreakpoint(0.2, 0.7);
    brkpts->addBreakpoint(0.05, 0.66);
    auto times = brkpts->getTimes();
    std::cout << "size: " << times.size() << std::endl;
    for (const double& t : times)
        std::cout << t << std::endl;
    return 0;
}
