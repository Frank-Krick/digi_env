#ifndef __UI__VIEWS__MENU__LEVEL__2__VIEW
#define __UI__VIEWS__MENU__LEVEL__2__VIEW

#include <string>

#include <daisy_patch.h>

constexpr unsigned int max_width = 128;
constexpr unsigned int max_height = 64 - 10;
constexpr unsigned int margin = 2;
constexpr unsigned int small_box_height = static_cast<unsigned int>((max_height - margin) / 2);
constexpr unsigned int usable_width_excluding_margin = max_width - margin * 8;
constexpr unsigned int box_width = static_cast<unsigned int>(usable_width_excluding_margin / 4);
constexpr unsigned int text_offset = static_cast<unsigned int>(box_width / 2) - 3; 

const unsigned int max_selected = 7;

namespace ui::views {
    class MenuLevel2View {
        public:
            MenuLevel2View(daisy::DaisyPatch & hardware): _hardware(hardware), _selected(0) {}
        
            void processInput() {
                if (_hardware.encoder.Increment() == -1) {
                    auto newSelected = (int)_selected - 1;
                    _selected = newSelected < 0 ? max_selected - 1 : newSelected;
                } else if (_hardware.encoder.Increment() == 1) {
                    _selected = (_selected + 1) % max_selected;
                }
            }

            void paint() {
                _drawTitle();

                int x = margin;
                for (unsigned int i = 0; i < 4; i++) {
                    if (i < 3) {
                        _drawUpperSmallRect(x, std::to_string(i + 1), i == _selected);
                        _drawLowerSmallRect(x, std::to_string(i + 4), i + 3 == _selected);
                    } else {
                        _drawFullRect(x, "S", 6 == _selected);
                    }

                    x += margin + box_width;
                }
            }

            unsigned int getSelected() {
                return _selected;
            }

        private:
            daisy::DaisyPatch & _hardware;
            unsigned int _selected;

            void _drawTitle()
            {
                _hardware.display.Fill(false);
                _hardware.display.SetCursor(0, 0);
                std::string title = "Select Envelope";
                _hardware.display.WriteString(title.c_str(), Font_7x10, true);
            }

            void _drawUpperSmallRect(unsigned int x, std::string number, bool selected) {
                _hardware.display.DrawRect(x, 10, x + box_width, 10 + small_box_height, true, selected);
                _hardware.display.SetCursor(x + text_offset, 20);
                _hardware.display.WriteString(number.c_str(), Font_7x10, !selected);
            }

            void _drawLowerSmallRect(unsigned int x, std::string number, bool selected) {
                _hardware.display.DrawRect(x, 10 + small_box_height + margin, x + box_width, 63, true, selected);
                _hardware.display.SetCursor(x + text_offset, 20 + small_box_height + margin);
                _hardware.display.WriteString(number.c_str(), Font_7x10, !selected);
            }

            void _drawFullRect(unsigned int x, std::string number, bool selected) {
                _hardware.display.DrawRect(x, 10, x + box_width, 63, true, selected);
                _hardware.display.SetCursor(x + text_offset, small_box_height + margin + 5);
                _hardware.display.WriteString(number.c_str(), Font_7x10, !selected);
            }
    };
}

#endif
