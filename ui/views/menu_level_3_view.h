#ifndef __UI__VIEWS__MENU__LEVEL__3__VIEW__
#define __UI__VIEWS__MENU__LEVEL__3__VIEW__

#include <daisy_patch.h>

#include "../model.h"
#include "../controller.h"
#include "midi_setup_view.h"
#include "sync_setup_view.h"

namespace ui::views {
    enum Level2ViewTypes {
        MidiSetupViewType,
        SyncSetupViewType
    };

    const int level_3_max_view_types = 2;

    class MenuLevel3View {
        public:
            MenuLevel3View(daisy::DaisyPatch & hardware, const Model & model, Controller & controller):
                _hardware(hardware),
                _model(model),
                _controller(controller),
                _midiSetupView(hardware),
                _syncSetupView(hardware),
                _activeView(MidiSetupViewType) {}

            void processInput() {
                if (_hardware.encoder.Increment() == -1) {
                    auto newActiveView = _activeView - 1;
                    if (newActiveView < 0) {
                        _activeView = (Level2ViewTypes)(level_3_max_view_types - 1);
                    } else {
                        _activeView = (Level2ViewTypes)newActiveView;
                    }
                } else if (_hardware.encoder.Increment() == 1) {
                    _activeView = (Level2ViewTypes)((_activeView + 1) % level_3_max_view_types);
                }
            }

            void paint() {
                switch (_activeView)
                {
                case MidiSetupViewType:
                    _midiSetupView.paint();
                    break;
                
                case SyncSetupViewType:
                    _syncSetupView.paint();
                    break;
                
                default:
                    break;
                }
            }

        private:
            daisy::DaisyPatch & _hardware;
            const Model & _model;
            Controller & _controller;
            MidiSetupView _midiSetupView;
            SyncSetupView _syncSetupView;
            Level2ViewTypes _activeView;
    };
}

#endif
