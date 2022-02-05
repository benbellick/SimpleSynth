#pragma once
#include <vector>
#include "osc_interface.hpp"

class LookupOsc : public Osc {
    public:
        enum InterpType {
            Truncate,
            LinearInterp
        };
        LookupOsc(
            std::shared_ptr<const std::vector<double>> lookupTable,
            InterpType interpType = LinearInterp
        );
        double getFreq() const override;
        void updateFreq(double freq) override;
        double next() override;
        void reset() override;
    private:
        void boundCurPhase();
        double m_curFreq;
        double m_curPhase;
        double m_incr;
        const InterpType m_interpType;
        //TODO: Later maybe find a way to make this an array, as
        //we don't need the dynamic ability of vector. However,
        //it is easier for now. In fact, should be made into its own
        //class so that the user does not have to manage gaurd point.
        //For now, we assume no gaurd point
        const std::shared_ptr<const std::vector<double>> m_lookupTable;
};
