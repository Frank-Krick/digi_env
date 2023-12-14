#ifndef __UI__VIEWS__RANGE__VIEW__
#define __UI__VIEWS__RANGE__VIEW__

#include <string>

#include <daisy_patch.h>

namespace ui::views {
    class RangeView {
        public:
            RangeView(daisy::DaisyPatch & hardware): _hardware(hardware) {}

            void paint() {
                _hardware.display.Fill(false);
                _hardware.display.SetCursor(0, 0);
                std::string title = "Range";
                _hardware.display.WriteString(title.c_str(), Font_7x10, true);
            }

        private:
            daisy::DaisyPatch & _hardware;
    };
}

#endif
