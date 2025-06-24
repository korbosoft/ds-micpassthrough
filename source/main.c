#include <nds.h>
#include <stdio.h>

//the record sample rate
#define sample_rate 8000

//buffer which is written to by the arm7
u16* mic_buffer = 0;

//the length of the current data
u32 data_length = 0;

// second long buffer
u32 mic_buffer_size = sample_rate * 2 ;


//mic stream handler
void micHandler(void *data, int length)
{
	soundEnable();
	soundPlaySample(data, SoundFormat_16Bit, length, sample_rate, 127, 64, false, 0);
}

int main(void)
{
	bool mute = false;

	const PrintConsole *console = consoleGetDefault();

	mic_buffer = (u16*)malloc(mic_buffer_size);

	videoSetModeSub(MODE_0_2D);
	vramSetBankC(VRAM_C_SUB_BG);

	consoleInit(NULL, console->bgLayer, BgType_Text4bpp, BgSize_T_256x256, console->mapBase, console->gfxBase, false, true);

	while (pmMainLoop())
	{
		consoleClear();
		iprintf("\x1b[2J"
			"DS Microphone Passthrough\n"
			"by Korbosoft\n"
			"\n"
			"Plug your DS into your\n"
			"device's microphone jack!\n"
			"\n");
		scanKeys();
		if (!mute) {
			iprintf("Press A to mute.\n");
			soundMicRecord(mic_buffer, mic_buffer_size, MicFormat_12Bit, sample_rate, micHandler);
		} else {
			memset(mic_buffer, 0, mic_buffer_size);
			iprintf("Press A to unmute.\n");
		}
		if (keysDown() & KEY_START) break;
		if (keysDown() & KEY_A)
			mute = !mute;

		iprintf("\n"
		"Press START to exit.\n");
		swiWaitForVBlank();
	}

	free(mic_buffer);

	return 0;
}
