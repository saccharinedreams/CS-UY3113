#include "Scene.h"
class Level3 : public Scene {

public:
	void Initialize(int livesLeft) override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
};