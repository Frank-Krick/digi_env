#include "daisy_patch.h"
#include "daisysp.h"

#include "ui/user_interface.h"

#include "processing/processor.h"

using namespace daisy;
using namespace daisysp;
using namespace ui;

DaisyPatch            hardware;
ui::UserInterface     userInterface(hardware);
processing::Processor processor(userInterface.getModel(), hardware);

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    if(hardware.gate_input[0].Trig())
    {
        processor.processGate(0);
    }

    if(hardware.gate_input[1].Trig())
    {
        processor.processGate(1);
    }

    processor.process(in, out, size);
}

int main(void)
{
    hardware.Init();
    hardware.StartAdc();
    hardware.StartAudio(AudioCallback);
    processor.setSampleRate(hardware.AudioSampleRate());

    for(;;)
    {
        userInterface.processInput();
        userInterface.paint();
		processor.outputCv();

        hardware.DelayMs(1);
    }
}
