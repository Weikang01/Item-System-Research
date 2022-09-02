#include <entt/entt.hpp>
#include <string>

class singl
{
private:
	singl() { std::puts("new singl created!"); }
public:
	singl(singl const&) = delete;
	void operator=(singl const&) = delete;

	static singl& getInstance()
	{
		static singl inst;
		return inst;
	}

	void playGame()
	{
		std::puts("playing games!");
	}
};

int main()
{
	singl::getInstance().playGame();

	struct TransformComponent
	{
		float x, y, z;
		TransformComponent()
			:x(0.f), y(0.f), z(0.f) {}

		TransformComponent(float&& x, float&& y, float&& z)
			: x(std::move(x)), y(std::move(y)), z(std::move(z)) {}
	};
	std::vector<TransformComponent> test_a;
	test_a.emplace_back(0.f, 0.f, 0.f).x = 10.0f;
	test_a.emplace_back(1.f, 1.f, 1.f).x;
	test_a.emplace_back(2.f, 2.f, 2.f).x;

	std::puts(std::to_string(test_a[0].x).c_str());


	entt::registry m_registry;
	entt::entity e1 = m_registry.create();
	m_registry.emplace<TransformComponent>(e1);

	return 0;
}