class Osc {
    public:
        Osc(unsigned long srate);
    private:
        double m_sampleRate;
        double m_curFreq;
        double m_curPhase;
        double m_incr;
};
