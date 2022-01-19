#pragma once

//For now, we assume sin, we will alter later
class Osc {
    public:
        Osc(unsigned long srate);
        void updateFreq(double freq);
        double tick();
    private:
        void boundCurPhase();
        double m_sampleRate;
        double m_curFreq;
        double m_curPhase;
        double m_incr;
};
