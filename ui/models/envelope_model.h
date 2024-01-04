#ifndef __UI__MODELS__ENVELOPE__MODEL__
#define __UI__MODELS__ENVELOPE__MODEL__

#include "duration.h"

namespace ui::models {
    enum CurveType { Linear, Logarithmic, Exponential };

    class EnvelopeModel {
        public:
            EnvelopeModel():
                    _attack(0),
                    _release(0),
                    _curveType(Linear) {}
        
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

            void setCurveType(CurveType curveType) {
                _curveType = curveType;
            }

            CurveType getCurveType() const {
                return _curveType;
            }

        private:
            Duration _attack;
            Duration _release;
            CurveType _curveType;
    };
}

#endif
