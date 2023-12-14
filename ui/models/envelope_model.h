#ifndef __UI__MODELS__ENVELOPE__MODEL__
#define __UI__MODELS__ENVELOPE__MODEL__

#include "duration_model.h"

namespace ui::models {
    class EnvelopeModel {
        public:
            EnvelopeModel(
                unsigned int attackInMs,
                unsigned int holdInMs,
                unsigned int decayInMs,
                unsigned int releaseInMs,
                double sustainLevel):
                    _attack(attackInMs),
                    _hold(holdInMs),
                    _decay(decayInMs),
                    _release(releaseInMs),
                    _sustain(sustainLevel) {}
        
            void setAttackInMs(unsigned int duration) { _attack.setDurationinMs(duration); }
            unsigned int getAttackInMs() const { return _attack.getDurationInMs(); }

            void setHoldInMs(unsigned int duration) { _hold.setDurationinMs(duration); }
            unsigned int getHoldInMs() const { return _hold.getDurationInMs(); }

            void setDecayInMs(unsigned int duration) { _decay.setDurationinMs(duration); }
            unsigned int getDecayInMs() const { return _decay.getDurationInMs(); }

            void setReleaseInMs(unsigned int duration) { _release.setDurationinMs(duration); }
            unsigned int getReleaseInMs() const { return _release.getDurationInMs(); }

            void setSustain(double level) { _sustain = level; }
            double getSustain() const { return _sustain; }

        private:
            DurationModel _attack;
            DurationModel _hold;
            DurationModel _decay;
            DurationModel _release;
            double _sustain;
    };
}

#endif
