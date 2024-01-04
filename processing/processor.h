#ifndef __PROCESSING__PROCESSOR__
#define __PROCESSING__PROCESSOR__

#include <array>

#include "daisy_patch.h"
#include "daisysp.h"

#include "envelope.h"

#include "../ui/model.h"

namespace processing
{
class Processor
{
  public:
    Processor(const ui::Model &model, daisy::DaisyPatch &hardware)
    : _model(model),
      _sampleRate(0),
      _envelopes{Envelope(model, 0, 0),
                 Envelope(model, 0, 1),
                 Envelope(model, 0, 2),
                 Envelope(model, 0, 3),
                 Envelope(model, 0, 4),
                 Envelope(model, 0, 5)},
      _hardware(hardware)
    {
    }

    void processGate(unsigned int gateId)
    {
        if(gateId == 0)
        {
            _envelopes[0].trigger();
            _envelopes[1].trigger();
            _envelopes[2].trigger();
        }
        else if(gateId == 1)
        {
            _envelopes[3].trigger();
            _envelopes[4].trigger();
            _envelopes[5].trigger();
        }
    }

    void process(daisy::AudioHandle::InputBuffer  in,
                 daisy::AudioHandle::OutputBuffer out,
                 size_t                           size)
    {
        for(size_t i = 0; i < size; i++)
        {
            for(auto &&envelope : _envelopes)
            {
                envelope.process();
            }

            for(unsigned int channel = 0; channel < 4; channel++)
            {
                out[channel][i]
                    = _envelopes[channel].getValue() * in[channel][i];
            }
        }
    }

    void outputCv()
    {
        _hardware.seed.dac.WriteValue(daisy::DacHandle::Channel::ONE,
                                      _envelopes[0].getValue() * 4095);
        _hardware.seed.dac.WriteValue(daisy::DacHandle::Channel::TWO,
                                      _envelopes[1].getValue() * 4095);
    }

    void setSampleRate(unsigned int sampleRate)
    {
        _sampleRate = sampleRate;
        for(auto &&envelope : _envelopes)
        {
            envelope.setSampleRate(sampleRate);
        }
    }

  private:
    const ui::Model        &_model;
    unsigned int            _sampleRate;
    std::array<Envelope, 6> _envelopes;
    daisy::DaisyPatch      &_hardware;
};
} // namespace processing

#endif
