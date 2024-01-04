#ifndef __UI__CURVE__VIEW__
#define __UI__CURVE__VIEW__

#include <string>

#include <daisy_patch.h>

namespace ui::views
{
class CurveView
{
  public:
    CurveView(daisy::DaisyPatch &hardware,
              const Model       &model,
              Controller        &controller)
    : _hardware(hardware), _model(model), _controller(controller)
    {
    }

    void paint()
    {
        _drawBackgroundAndHeader();
        _drawCurveType();
    }

    void processInput() {
        auto curveControlValue = _hardware.controls[0].Value();
        if (curveControlValue < 0.33) {
            _controller.setEnvelopeCurveType(ui::models::CurveType::Logarithmic);
        } else if (curveControlValue < 0.66) {
            _controller.setEnvelopeCurveType(ui::models::CurveType::Linear);
        } else {
            _controller.setEnvelopeCurveType(ui::models::CurveType::Exponential);
        }
    }

  private:
    daisy::DaisyPatch &_hardware;
    const Model       &_model;
    Controller        &_controller;

    void _drawBackgroundAndHeader()
    {
        _hardware.display.Fill(false);
        _hardware.display.SetCursor(0, 0);
        std::string title = "Curves";
        _hardware.display.WriteString(title.c_str(), Font_7x10, true);
    }

    void _drawCurveType()
    {
        auto curveType = _model.getSelectedEnvelope().getCurveType();
        _hardware.display.SetCursor(0, 10);

        switch(curveType)
        {
            case ui::models::CurveType::Linear:
                _hardware.display.WriteString("lin", Font_7x10, true);
                break;

            case ui::models::CurveType::Exponential:
                _hardware.display.WriteString("exp", Font_7x10, true);
                break;

            case ui::models::CurveType::Logarithmic:
                _hardware.display.WriteString("log", Font_7x10, true);
                break;

            default: break;
        }
    }
};
} // namespace ui::views

#endif
