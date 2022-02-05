#pragma once

#include <vector>

#include "stream_interface.hpp"

class Envelope : public StreamInterface {
    public:
        Envelope();
        ~Envelope() {};
        size_t size() const;
        double next() override;
        void reset() override;
        void addBreakpoint(double time, double value);
        std::vector<double> getTimes() const; //For debugging purposes
    private:
        struct Breakpoint {
            Breakpoint(double time, double value) : time(time), value(value) {};
            double time;
            double value;
        };

        std::vector<Breakpoint> m_breakpoints;
        std::vector<Breakpoint>::const_iterator m_currentLocation;
        double m_curTime;
};
