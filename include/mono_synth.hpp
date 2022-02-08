#include <memory>

#include "osc_interface.hpp"
#include "stream_interface.hpp"

class MonoSynth : public StreamInterface {
    public:
        MonoSynth(
            std::shared_ptr<Osc> osc,
            std::shared_ptr<StreamInterface> ampEnvelope,
            std::shared_ptr<StreamInterface> freqEnvelope
        );
        double next() override;
        void reset() override;
    private:
        std::shared_ptr<Osc> m_osc;
        std::shared_ptr<StreamInterface> m_ampEnvelope;
        std::shared_ptr<StreamInterface> m_freqEnvelope;
};
