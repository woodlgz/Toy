/*
 * trial.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: woodlgz
 */

#include <string>
#include <assert.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

#define RES_FOLDER	"./Res"

using namespace std;

class GameException{
public:
	GameException():message("GameException caused by unknown reason"){
	}
	GameException(const char* str):message(str){
	}
	const char* getMessage(){
		return message;
	}
private:
	const char* message;
};

class GameApp{
public:
	static const int WIDTH 		= 640;
	static const int HEIGHT 	= 480;
	static const int BITDEPTH 	= 32;
public:
	GameApp(){
		m_Screen = NULL;
		m_Picture  = NULL;
	}
	virtual ~GameApp(){
		if(!m_Cleaned)
				cleanUp();
	}
	virtual void run(){
		bool isEnd = false;
		while(!isEnd){
			while(SDL_PollEvent(&m_Event)){
				switch(m_Event.type){
				case SDL_QUIT:
					isEnd = true;
					break;
				}
			}
		}
		cleanUp();
	}
	virtual void init(){
			m_Cleaned = false;
			SDL_Init(SDL_INIT_EVERYTHING);
			m_Screen = SDL_SetVideoMode(WIDTH,HEIGHT,BITDEPTH,SDL_SWSURFACE);
			assert(m_Screen != NULL || errorExit(SDL_GetError()));
			SDL_Surface* tmp = IMG_Load((string(RES_FOLDER)+"/1.jpg").c_str());
			assert(tmp != NULL || errorExit(SDL_GetError()));
			m_Picture = SDL_DisplayFormat(tmp);
			SDL_FreeSurface(tmp);
			assert(SDL_BlitSurface(m_Picture,NULL,m_Screen,NULL)>=0 || errorExit(SDL_GetError()));
			assert(SDL_Flip(m_Screen)>=0 || errorExit(SDL_GetError()));
	}
	virtual void cleanUp(){
			SDL_FreeSurface(m_Picture);
			SDL_Quit();
			m_Cleaned = true;
	}
protected:
	virtual bool errorExit(const char* message){
		if(!m_Cleaned)
				cleanUp();
		throw GameException(message);
		return false;
	}
protected:
	SDL_Surface* m_Picture;
	SDL_Surface* m_Screen;
	SDL_Event m_Event;
	bool m_Cleaned;
};

int main(int argc,char** argv){
	GameApp* game = new GameApp();
	try{
		game->init();
		game->run();
	}catch(GameException e){
			printf("%s\n",e.getMessage());
	}
	delete game;
	return 0;
}
