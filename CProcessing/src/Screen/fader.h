#include <stdbool.h>

typedef enum
{
	FADE_IN,
	FADE_OUT

}FadeType;

typedef struct 
{
	FadeType fadeType;

	bool isFading;

	float fadeAlpha,

		  fadeSpeed,
		  fadePosX,
		  fadePosY;

}Fader;

void CreateFader(Fader* fader);
void StartFade(Fader* fader, FadeType fadeType);
void StopFade(Fader* fader, FadeType fadeType);
void UpdateFade(Fader* fader);
void ResetFader(Fader* fader);