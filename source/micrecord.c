#include <nds.h>
#include <stdio.h>

//the record sample rate
#define sample_rate  8000

//buffer which is written to by the arm7
u16* mic_buffer = 0;

//the length of the current data
u32 data_length = 0;

//the mic buffer sent to the arm7 is a double buffer
//every time it is half full the arm7 signals us so we can read the
//data.  I want the buffer to swap about once per frame so i chose a
//buffer size large enough to hold two frames of 16bit mic data
u32 mic_buffer_size = sample_rate * 2 / 30 ;


//mic stream handler
void micHandler(void* data, int length)
{
	soundEnable();
	soundPlaySample(data, SoundFormat_16Bit, length, sample_rate, 127, 64, false, 0);

}

int main(void)
{
	mic_buffer = (u16*)malloc(mic_buffer_size);

	consoleDemoInit();

	iprintf("Korbosoft DS Microphone Passthrough\n");

	while(pmMainLoop())
	{

		scanKeys();

		soundMicRecord(mic_buffer, mic_buffer_size, MicFormat_12Bit, sample_rate, micHandler);

		if(keysDown() & KEY_START) break;

		swiWaitForVBlank();

	}

	free(mic_buffer);
}
