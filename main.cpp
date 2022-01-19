#include <iostream>
#include <memory>
#include <sndfile.h>

#include "osc.hpp"

int main() {
    //std::shared_ptr<Osc> osc = std::make_shared<Osc>(44100);
    std::shared_ptr<int> osc = std::make_shared<int>(5);
    std::cout << "test" << std::endl;
    //std::shared_ptr<int> foo = std::make_shared<int>(10);
    //std::shared_ptr<int> foo2 (new int(10));
    return 0;
}
