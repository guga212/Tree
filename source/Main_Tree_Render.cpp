#include "TreeRenderer.h"

int main()
{
	auto root = Node<float>::CreateRootNode(3.0f);
	auto child1=root->CreateChildNode(4.0f);
	auto child2=root->CreateChildNode(6.0f);
	auto child11 =child1->CreateChildNode(2.0f);
	auto child12 = child1->CreateChildNode(1.0f);
	auto child13 = child1->CreateChildNode(18.0f);
	auto child21 = child2->CreateChildNode(3.0f);
	auto child22 = child2->CreateChildNode(43.0f);
	auto child3 = root->CreateChildNode(1.0f);
	auto child31 = child3->CreateChildNode(1.0f);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Rendering!");
	TreeRenderer<float> treeRenderer(root,&window,0.f,0.0f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		treeRenderer.Draw();
		window.display();
	}

	return 0;
}