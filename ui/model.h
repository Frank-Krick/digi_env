#ifndef __UI__MODEL__
#define __UI__MODEL__

#include <array>

#include "models/envelope_model.h"

namespace ui {
    class Model {
        public:
            Model():
                _selectedEnvelope(0),
                _envelopes{
                    models::EnvelopeModel(10, 10, 10, 10, 1.0), 
                    models::EnvelopeModel(10, 10, 10, 10, 1.0), 
                    models::EnvelopeModel(10, 10, 10, 10, 1.0), 
                    models::EnvelopeModel(10, 10, 10, 10, 1.0), 
                    models::EnvelopeModel(10, 10, 10, 10, 1.0), 
                    models::EnvelopeModel(10, 10, 10, 10, 1.0)} {}

            void setSelectedEnvelopeIndex(unsigned int envelopeId) {
                _selectedEnvelope = envelopeId;
            }

            unsigned int getSelectedEnvelopeIndex() const {
                return _selectedEnvelope;
            }

            const models::EnvelopeModel & getSelectedEnvelope() const { return _envelopes[_selectedEnvelope]; }

        private:
            unsigned int _selectedEnvelope;
            std::array<models::EnvelopeModel, 6> _envelopes;
    };
}

#endif
