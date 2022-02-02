#include <vector>

#include "stream_interface.hpp"
#include "osc.hpp"

class OscBank : public StreamInterface {
    public:
        OscBank();
        OscBank(unsigned int numOfOscs);
        double next() override;
        void reset() override;

        void addOsc(std::shared_ptr<Osc> osc);
    private:
        std::vector<std::shared_ptr<Osc>> m_oscs;
};
