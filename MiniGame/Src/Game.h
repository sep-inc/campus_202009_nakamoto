#ifndef GAME_H_
#define GAME_H_

class Game
{
public:
	Game();

	virtual ~Game(){}

	virtual void Update() = 0;

	virtual void Draw() = 0;

	bool IsEnd() const { return m_IsEnd; };

protected:
	bool m_IsEnd;

};

#endif