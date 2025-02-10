#include <nds.h>
#include <stdio.h>

//the record sample rate
#define sample_rate  8000

//buffer which is written to by the arm7
u16* mic_buffer = 0;

//the length of the current data
u32 data_length = 0;

// second long buffer
u32 mic_buffer_size = sample_rate * 2 ;


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

	iprintf("Korbosoft DS Microphone\nPassthrough\nPlug your DS into your PC's microphone jack!");

	while(pmMainLoop())
	{

		scanKeys();

		soundMicRecord(mic_buffer, mic_buffer_size, MicFormat_12Bit, sample_rate, micHandler);

		if(keysDown() & KEY_START) break;

		swiWaitForVBlank();

	}

	free(mic_buffer);
}
