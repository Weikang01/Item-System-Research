#include <entt/entt.hpp>
#include <string>

int main()
{
	struct TransformComponent
	{
		float x, y, z;
		TransformComponent()
			:x(0.f), y(0.f), z(0.f) {}
		TransformComponent(float x, float y, float z)
			: x(x), y(y), z(z) {}
		TransformComponent(float&& x, float&& y, float&& z)
			: x(std::move(x)), y(std::move(y)), z(std::move(z)) {}
	};
	std::vector<int> test_a;
	test_a.emplace_back(1);
	test_a.emplace_back(1);
	std::puts(std::to_string(test_a.size()).c_str());

	entt::registry m_registry;
	entt::entity e1 = m_registry.create();
	m_registry.emplace<TransformComponent>(e1);

	return 0;
}