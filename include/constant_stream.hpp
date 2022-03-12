#include "stream_interface.hpp"

class ConstantStream : public StreamInterface {
    public:
        ConstantStream(const double value);
        double next() override;
        void next(Buffer<double>& buffer) override;
        void reset() override;
    private:
        const double m_value;
};
