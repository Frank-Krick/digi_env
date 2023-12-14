#ifndef __UI__VIEWS__MIDI__SETUP__VIEW__
#define __UI__VIEWS__MIDI__SETUP__VIEW__

#include <string>

#include <daisy_patch.h>

namespace ui::views {
    class MidiSetupView {
        public:
            MidiSetupView(daisy::DaisyPatch & hardware): _hardware(hardware) {}

            void paint() {
                _hardware.display.Fill(false);
                _hardware.display.SetCursor(0, 0);
                std::string title = "Midi Setup";
                _hardware.display.WriteString(title.c_str(), Font_7x10, true);
            }
        
        private:
            daisy::DaisyPatch & _hardware;
    };
}

#endif
