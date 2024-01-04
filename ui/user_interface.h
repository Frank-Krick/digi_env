#ifndef __UI__USER__INTERFACE__
#define __UI__USER__INTERFACE__

#include <memory>

#include <daisy_patch.h>

#include "controller.h"
#include "view.h"
#include "model.h"

namespace ui {
    class UserInterface {
        public:
            UserInterface(daisy::DaisyPatch & hardware):
                _model(),
                _controller(_model),
                _view(hardware, _model, _controller) {}

            void processInput() { _view.processInput(); }
            void paint() { _view.paint(); }

            const Model & getModel() const { return _model; }

        private:
            Model _model;
            Controller _controller;
            View _view;
    };
}

#endif
