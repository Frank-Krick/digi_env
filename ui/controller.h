#ifndef __UI__CONTROLLER__
#define __UI__CONTROLLER__

#include "model.h"

namespace ui {
    class Controller {
        public:
            explicit Controller(Model & model): _model(model) {}

            void selectEnvelope(unsigned int envelopeId) {
                _model.setSelectedEnvelopeIndex(envelopeId);
            }

            void setEnvelopeAttackInMs(unsigned int attackMs) {
                _model.getSelectedEnvelope().setAttackInMs(attackMs);
            }

            void setEnvelopeReleaseInMs(unsigned int releaseMs) {
                _model.getSelectedEnvelope().setReleaseInMs(releaseMs);
            };

        private:
            Model & _model;
    };
}

#endif
