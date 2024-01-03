#ifndef __UI__MODELS__ENVELOPE__MODEL__
#define __UI__MODELS__ENVELOPE__MODEL__

#include "duration.h"

namespace ui::models {
    class EnvelopeModel {
        public:
            EnvelopeModel():
                    _attack(0),
                    _release(0) {}
        
            void setAttackInMs(unsigned int duration) {
                _attack.setDurationinMs(duration);
            }

            unsigned int getAttackInMs() const {
                return _attack.getDurationInMs();
            }

            void setReleaseInMs(unsigned int duration) {
                _release.setDurationinMs(duration);
            }

            unsigned int getReleaseInMs() const {
                return _release.getDurationInMs();
            }

        private:
            Duration _attack;
            Duration _release;
    };
}

#endif
