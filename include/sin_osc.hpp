#pragma once
#include "osc_interface.hpp"

class SinOsc : public Osc {
    public:
        SinOsc();
        ~SinOsc() {};
        double getFreq() const override;
        void updateFreq(double freq) override;
        double next() override;
        void reset() override;
    private:
        void boundCurPhase();
};
