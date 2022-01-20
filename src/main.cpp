#include <iostream>
#include <memory>
#include <sndfile.h>

#include "osc.hpp"

int main() {
    std::shared_ptr<Osc> osc = std::make_shared<Osc>(44100);
    return 0;
}
