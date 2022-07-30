#pragma once

#include <windows.h>
class AudioManager {
	static AudioManager* s_pInstace;

	AudioManager() {

	}
public:
	static AudioManager* GetInstance() {
		if (s_pInstace == nullptr) {
			s_pInstace = new AudioManager();
			return s_pInstace;
		}
	}

	static void DestroyInstance() {
		delete s_pInstace;
		s_pInstace = nullptr;
	}
	void PlayDoorClosedSound()
	{
		Beep(500, 75);
		Beep(500, 75);
	}
	void PlayDoorOpenSound()
	{
		Beep(1397, 200);
	}

	void PlayKeyPickupSound()
	{
		Beep(1568, 200);
	}

	void PlayWinSound()
	{
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1245, 200);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1175, 1000);

	}

	void PlayMoneySound() {
		Beep(1568, 50);
	}

	void PlayLoseLiveSound()
	{
		Beep(200, 100);

	}

	void PlayLoseSound()
	{
		Beep(500, 75);
		Beep(500, 75);
		Beep(500, 75);
		Beep(500, 75);
	}
};