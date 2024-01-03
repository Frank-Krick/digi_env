#include "daisy_patch.h"
#include "daisysp.h"

#include "ui/user_interface.h"

using namespace daisy;
using namespace daisysp;
using namespace ui;

DaisyPatch hardware;
ui::UserInterface userInterface(hardware);

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	userInterface.processInput();
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
		out[2][i] = in[2][i];
		out[3][i] = in[3][i];
	}
}

int main(void)
{
	hardware.Init();
	
	hardware.StartAdc();
	hardware.StartAudio(AudioCallback);

    for(;;)
    {
		userInterface.paint();
		hardware.DelayMs(1);
    }
}
