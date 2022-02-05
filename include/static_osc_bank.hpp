#include <vector>

#include "osc_interface.hpp"
#include "sin_osc.hpp"

class StaticOscBank : public Osc {
    public:
        StaticOscBank(
            const unsigned int numOfOscs,
            const std::vector<double>& relativeAmps,
            const std::vector<double>& relativeFreqs,
            const double lowCutFreq = 20,
            const double highCutFreq = 20000
        );
        double next() override;
        void reset() override;
        double getFreq() const override;
        void updateFreq(double freq) override;
    private:
        const unsigned int m_numOfOscs;
        double m_curFreq;
        std::vector<std::unique_ptr<SinOsc>> m_oscs;
        std::vector<double> m_relativeAmps;
        std::vector<double> m_relativeFreqs; //relative to base freq multiplicative
        const double m_lowCutFreq;
        const double m_highCutFreq;
};
