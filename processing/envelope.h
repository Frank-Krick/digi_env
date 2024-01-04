#ifndef __PROCESSING__ENVELOPE__
#define __PROCESSING__ENVELOPE__

#include "../ui/model.h"

namespace processing
{
enum EnvelopePhase
{
    Attack,
    Release,
    Finished
};

class Envelope
{
  public:
    Envelope(const ui::Model &model,
             unsigned int     sampleRate,
             unsigned int     index)
    : _model(model), _sampleRate(sampleRate), _index(index), _phase(Attack)
    {
    }

    void trigger() { _triggered = true; }

    float process()
    {
        auto envelopeParameter = _model.getEnvelopeByIndex(_index);
        if(_triggered)
        {
            _triggered = false;
            _value     = 0.0f;
            _phase     = Attack;
        }
        else
        {
            if(_phase == Attack)
            {
                _attackPhase(envelopeParameter);
            }
            else if(_phase == Release)
            {
                _releasePhase(envelopeParameter);
            }
        }

        return _value;
    }

    float getValue() const { return _value; };

    void setSampleRate(unsigned int sampleRate) { _sampleRate = sampleRate; }

  private:
    const ui::Model &_model;
    unsigned int     _sampleRate;
    unsigned int     _index;
    bool             _triggered;
    EnvelopePhase    _phase;
    float            _value;

    void _attackPhase(ui::models::EnvelopeModel &envelopeParameter)
    {
        float attackTimeInSamples
            = (float)_sampleRate
              * ((float)envelopeParameter.getAttackInMs() / 1000.0f);

        _value += 1.0f / attackTimeInSamples;
        if(_value > 1.0f)
        {
            _value = 1.0f;
            _phase = Release;
        }
    }

    void _releasePhase(ui::models::EnvelopeModel &envelopeParameter)
    {
        float releaseTimeInSamples
            = (float)_sampleRate
              * ((float)envelopeParameter.getReleaseInMs() / 1000.0f);

        _value -= 1.0f / releaseTimeInSamples;
        if(_value < 0.0f)
        {
            _value = 0.0f;
            _phase = Finished;
        }
    }
};
} // namespace processing

#endif
