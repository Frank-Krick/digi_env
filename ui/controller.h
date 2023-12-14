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

        private:
            Model & _model;
    };
}

#endif
