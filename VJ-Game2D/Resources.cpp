#include "Resources.h"

const char* Resources::SPRITESHEET_GON = "res/sprites/char/gon.png";
const char* Resources::SPRITESHEET_KILLUA = "res/sprites/char/killua.png";
const char* Resources::LEVEL01 = "res/levels/AK.tmx";
const char* Resources::LEVEL02 = "res/levels/AK2.tmx";
const char* Resources::SPRITESHEET_JUMPING_FROG = "res/sprites/entities/enemy_frog.png";
const char* Resources::SPRITESHEET_EVIL_PTERO = "res/sprites/entities/enemy_bird.png";
const char* Resources::SPRITESHEET_EVIL_FISH = "res/sprites/entities/evilFish.png";
const char* Resources::SPRITESHEET_OCTO = "res/sprites/entities/octopus.png";
const char* Resources::SPRITESHEET_OCTO_BALL = "res/sprites/entities/octopus_ball.png";
const char* Resources::SPRITESHEET_HISO_CARD = "res/sprites/entities/card.png";
const char* Resources::SPRITESHEET_GHOST = "res/sprites/entities/boo.png";
const char* Resources::SPRITESHEET_HISOKA = "res/sprites/entities/hisoka.png";
const char* Resources::START_SCREEN0 = "res/sprites/start_menu/start_0.png";
const char* Resources::START_SCREEN1 = "res/sprites/start_menu/start_1.png";
const char* Resources::START_SCREEN2 = "res/sprites/start_menu/start_2.png";
const char* Resources::START_SCREEN3 = "res/sprites/start_menu/start_3.png";
const char* Resources::START_SCREEN4 = "res/sprites/start_menu/start_4.png";
const char* Resources::START_SCREEN = "res/sprites/start_menu/start_5.png";
const char* Resources::MAP_SCREEN = "res/sprites/start_menu/map_level.png";
const char* Resources::MAP_COVER = "res/sprites/start_menu/map_uncover.png";
const char* Resources::PUSH_START = "res/sprites/start_menu/push_start.png";
const char* Resources::FONT = "res/sprites/font.png";
const char* Resources::GUI_USING_GON = "res/sprites/GUI/using_gon.png";
const char* Resources::GUI_USING_KILLUA = "res/sprites/GUI/using_killua.png";
const char* Resources::HUNTER_LICENSE = "res/sprites/entities/hunter_license.png";
const char* Resources::PARTICLE_ROCK = "res/sprites/particle/rock.png";
const char* Resources::PARTICLE_EXPLOSION = "res/sprites/particle/explosion.png";
const char* Resources::PARTICLE_GON_GHOST = "res/sprites/particle/gon_ghost.png";
const char* Resources::PARTICLE_KILLUA_GHOST = "res/sprites/particle/killua_ghost.png";
const char* Resources::HELP_KEYS = "res/sprites/help/keys.png";

Resources::Resources()
{
}


Resources::~Resources()
{
}
const char* Resources::getResourceLevel(int level) {
	switch (level) {
	case 1:
		return LEVEL01;
		break;
	case 2:
		return LEVEL02;
		break;

	}
}