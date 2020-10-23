#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

enum class SceneList
{
	SCENE_SELECT,
	SCENE_GAME,
};

/*
	シーンの基底クラス
*/
class SceneBase
{
public:
	SceneBase();

	virtual ~SceneBase(){}

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual inline SceneList GetScene() const = 0;

	inline bool SceneEnd() { return m_SceneEnd; }

protected:
	bool m_SceneEnd;

};

#endif