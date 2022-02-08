#include <vector>

#include "osc_interface.hpp"
#include "lookup_osc.hpp"

class StaticOscBank : public Osc {
    public:
        StaticOscBank(
            const unsigned int numOfOscs,
            const std::vector<double>& relativeAmps,
            const std::vector<double>& relativeFreqs,
            const double lowCutFreq = 20,
            const double highCutFreq = 20000
        );
        //If lookup table is provided, we construct lookup oscillators
        StaticOscBank(
            const unsigned int numOfOscs,
            const std::vector<double>& relativeAmps,
            const std::vector<double>& relativeFreqs,
            const std::shared_ptr<const std::vector<double>> lookupTable,
            const Enums::InterpType interpType = Enums::InterpType::Linear,
            const double lowCutFreq = 20,
            const double highCutFreq = 20000
        );
        ~StaticOscBank(){};
        double next() override;
        void reset() override;
        double getFreq() const override;
        void updateFreq(double freq) override;
    private:
        const unsigned int m_numOfOscs;
        double m_curFreq;
        std::vector<std::unique_ptr<Osc>> m_oscs;
        std::vector<double> m_relativeAmps;
        std::vector<double> m_relativeFreqs; //relative to base freq multiplicative
        const double m_lowCutFreq;
        const double m_highCutFreq;
};
