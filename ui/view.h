#ifndef __UI__VIEW__
#define __UI__VIEW__

#include "views/menu_level_1_view.h"
#include "views/menu_level_2_view.h"
#include "views/menu_level_3_view.h"

namespace ui {
    class View {
        public:
            View(daisy::DaisyPatch & hardware, const Model & model, Controller & controller):
                _menuLevel(0),
                _hardware(hardware),
                _menuLevel1View(hardware, model, controller),
                _menuLevel2View(hardware),
                _menuLevel3View(hardware, model, controller),
                _controller(controller) {}

            void processInput() {
                _hardware.ProcessAllControls();

                if (_hardware.encoder.RisingEdge()) {
                    _updateSelectedMenuLevel();
                } else {
                    _processMenuLevel();
                }
            }

            void paint() {
                switch(_menuLevel) {
                    case 0:
                        _menuLevel1View.paint();
                        break;
                    
                    case 1:
                        _menuLevel2View.paint();
                        break;
                    
                    case 2:
                        _menuLevel3View.paint();
                        break;

                    default:
                        break;
                }
                _hardware.display.Update();
            }

        private:
            unsigned int _menuLevel;
            daisy::DaisyPatch & _hardware;
            views::MenuLevel1View _menuLevel1View;            
            views::MenuLevel2View _menuLevel2View;
            views::MenuLevel3View _menuLevel3View;            
            Controller & _controller;


            void _updateSelectedMenuLevel()
            {
                if(_menuLevel == 1)
                {
                    auto selected = _menuLevel2View.getSelected();
                    if(selected < 6)
                    {
                        _controller.selectEnvelope(selected);
                        _menuLevel = 0;
                    }
                    else
                    {
                        _menuLevel = 2;
                    }
                }
                else
                {
                    _menuLevel = 1;
                }
            }

            void _processMenuLevel()
            {
                switch(_menuLevel)
                {
                    case 0: _menuLevel1View.processInput(); break;

                    case 1: _menuLevel2View.processInput(); break;

                    case 2: _menuLevel3View.processInput(); break;

                    default: break;
                }
            }
    };
}

#endif
