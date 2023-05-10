#include <ComFunc.hpp>
bool checkCollision(const SDL_Rect& object1,const SDL_Rect& object2) {

	if (object1.x + object1.w > object2.x && object1.x < object2.x + THREAT_WIDTH && object1.y + bird_h > object2.y && object1.y < object2.y + THREAT_HEIGHT) {
		return true;
	}
	return false;
}



