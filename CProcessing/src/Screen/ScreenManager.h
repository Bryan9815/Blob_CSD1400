typedef enum {
	INTRO,
	MAIN_MENU,
	OPTION,
	GAMEPLAY,
	CREDITS,
}GameState;

void GameInit(void);
void GameUpdate(void);
void GameExit(void);
void SetGameState(GameState nextState);