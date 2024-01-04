#ifndef __UI__MENU__LEVEL__1__VIEW__
#define __UI__MENU__LEVEL__1__VIEW__

#include <daisy_patch.h>

#include "../model.h"
#include "../controller.h"
#include "envelope_view.h"
#include "curve_view.h"
#include "envelope_setup_view.h"
#include "range_view.h"
#include "effects_view.h"
#include "output_view.h"
#include "trigger_view.h"

namespace ui::views {
    enum Level1ViewTypes {
        EnvelopeSetupViewType = 0,
        EnvelopeViewType,
        CurveViewType,
        RangeViewType,
        EffectsViewType,
        OutputViewType,
        TriggerViewType
    };

    const int max_view_types = 7;

    class MenuLevel1View {
        public:
            MenuLevel1View(daisy::DaisyPatch & hardware, const Model & model, Controller & controller): 
                _model(model),
                _controller(controller),
                _hardware(hardware),
                _envelopeSetupView(hardware),
                _envelopeView(hardware, model, controller),
                _curveView(hardware, model, controller),
                _rangeView(hardware),
                _effectsView(hardware),
                _outputView(hardware),
                _triggerView(hardware),
                _activeView(EnvelopeViewType) {}

            void processInput() {
                if (_hardware.encoder.Increment() == -1) {
                    auto newActiveView = _activeView - 1;
                    if (newActiveView < 0) {
                        _activeView = (Level1ViewTypes)(max_view_types - 1);
                    } else {
                        _activeView = (Level1ViewTypes)newActiveView;
                    }
                } else if (_hardware.encoder.Increment() == 1) {
                    _activeView = (Level1ViewTypes)((_activeView + 1) % max_view_types);
                } else {
                    switch (_activeView)
                    {
                    case EnvelopeViewType:
                        _envelopeView.processInput();
                        break;
                    
                    case CurveViewType:
                        _curveView.processInput();
                        break;

                    default:
                        break;
                    }
                }
            }

            void paint() {
                switch (_activeView)
                {
                case EnvelopeSetupViewType:
                    _envelopeSetupView.paint();
                    break;

                case EnvelopeViewType:
                    _envelopeView.paint();
                    break;

                case CurveViewType:
                    _curveView.paint();
                    break;

                case RangeViewType:
                    _rangeView.paint();
                    break;

                case EffectsViewType:
                    _effectsView.paint();
                    break;

                case OutputViewType:
                    _outputView.paint();
                    break;

                case TriggerViewType:
                    _triggerView.paint();
                    break;

                default:
                    break;
                }

                _drawActiveEnvelopeIndicator();
            }

        private:
            const Model & _model;
            Controller & _controller;
            daisy::DaisyPatch & _hardware;
            EnvelopeSetupView _envelopeSetupView;
            EnvelopeView _envelopeView;
            CurveView _curveView;
            RangeView _rangeView;
            EffectsView _effectsView;
            OutputView _outputView;
            TriggerView _triggerView;
            Level1ViewTypes _activeView;

            void _drawActiveEnvelopeIndicator()
            {
                _hardware.display.SetCursor(127 - 7, 0);
                auto selectedEnvelope
                    = std::to_string(_model.getSelectedEnvelopeIndex() + 1);
                _hardware.display.WriteString(
                    selectedEnvelope.c_str(), Font_7x10, true);
            }
    };
}

#endif
