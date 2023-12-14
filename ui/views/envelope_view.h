#ifndef __UI__VIEWS__ENVELOPE__VIEW__
#define __UI__VIEWS__ENVELOPE__VIEW__

#include <string>

#include <daisy_patch.h>

#include "../model.h"

namespace ui::views {
    class EnvelopeView {
        public:
            EnvelopeView(daisy::DaisyPatch & hardware, const Model & model):
                _hardware(hardware),
                _model(model) {}

            void paint() {
                _drawHeader();

                auto envelope = _model.getSelectedEnvelope();
            }

        private:
            daisy::DaisyPatch & _hardware;
            const Model & _model;

            void _drawHeader()
            {
                _hardware.display.Fill(false);
                _hardware.display.SetCursor(0, 0);
                std::string title = "Envelope";
                _hardware.display.WriteString(title.c_str(), Font_7x10, true);
            }
    };
}

#endif
