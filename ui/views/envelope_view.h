#ifndef __UI__VIEWS__ENVELOPE__VIEW__
#define __UI__VIEWS__ENVELOPE__VIEW__

#include <string>

#include <daisy_patch.h>

#include "../model.h"
#include "../controller.h"

namespace ui::views {
    constexpr unsigned int quarter_screen_width = 128 / 4;
    constexpr unsigned int text_y_position = 20;

    class EnvelopeView {
        public:
            EnvelopeView(daisy::DaisyPatch & hardware, const Model & model, Controller & controller):
                _hardware(hardware),
                _model(model),
                _controller(controller) {}

            void paint() {
                _drawHeader();

                auto envelope = _model.getSelectedEnvelope();

                _drawAttackValue(envelope);
                _drawReleaseValue(envelope);
            }

            void processInput() {
                auto attackControlValue = _hardware.controls[0].Value();
                _controller.setEnvelopeAttackInMs(attackControlValue * 1000);

                auto releaseControlValue = _hardware.controls[1].Value();
                _controller.setEnvelopeReleaseInMs(releaseControlValue * 1000);
            }

        private:
            daisy::DaisyPatch & _hardware;
            const Model & _model;
            Controller & _controller;

            void _drawHeader()
            {
                _hardware.display.Fill(false);
                _hardware.display.SetCursor(0, 0);
                std::string title = "Envelope";
                _hardware.display.WriteString(title.c_str(), Font_7x10, true);
            }
            
            void _drawAttackValue(const models::EnvelopeModel & envelope) {
                _hardware.display.SetCursor(0, text_y_position);
                auto attack = std::to_string(envelope.getAttackInMs());
                _hardware.display.WriteString(attack.c_str(), Font_7x10, true);
            }
            
            void _drawReleaseValue(const models::EnvelopeModel & envelope) {
                _hardware.display.SetCursor(quarter_screen_width, text_y_position);
                auto release = std::to_string(envelope.getReleaseInMs());
                _hardware.display.WriteString(release.c_str(), Font_7x10, true);
            }
    };
}

#endif
