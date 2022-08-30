#include "ECS.h"
#include "Components.h"

int main()
{
	Manager manager;
	Entity& e1(manager.addEntity());
	Entity& e2(manager.addEntity());
	e1.addComponent<PositionComponent>();
	e2.addComponent<PositionComponent>();
	e1.getComponent<PositionComponent>().setPos(10, 10);
	e2.getComponent<PositionComponent>().setPos(3, 3);
	manager.update();

	std::cout << e1.getComponent<PositionComponent>().x() << std::endl;
	std::cout << e2.getComponent<PositionComponent>().x() << std::endl;

	return 0;
}