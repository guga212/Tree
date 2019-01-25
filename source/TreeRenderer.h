#ifndef __TREE_RENDERER_H__
#define __TREE_RENDERER_H__
#include "Node.h"
#include "SFML/Graphics.hpp"


template <class T>
class TreeRenderer
{
	struct Pos2D { float x; float y; };
public:
	TreeRenderer(std::shared_ptr<Node<T>> startNode, sf::RenderWindow* w, float treePosX, float treePosY, uint16_t r = 30):window(w),radius(r)
	{
		
		std::function<void(std::shared_ptr<Node<T>> node, Pos2D nodePos, Pos2D parentPos, std::vector<Pos2D>& nodesPos, std::vector<std::pair<Pos2D, Pos2D>>& connectionsPos)> RecursivePositionCalculation;
		float maxWidth = 0;
		float shiftLength = 3.5f*r;

		RecursivePositionCalculation = [&RecursivePositionCalculation,&maxWidth,&shiftLength](std::shared_ptr<Node<T>> node, Pos2D nodePos, Pos2D parentPos, std::vector<Pos2D>& nodesPos, std::vector<std::pair<Pos2D, Pos2D>>& connectionsPos)
		{	
			maxWidth = std::max(maxWidth, nodePos.x);
			connectionsPos.push_back({ parentPos, nodePos });			
			nodesPos.push_back(nodePos);
			Pos2D nextNodePos { nodePos.x, nodePos.y + shiftLength };

			auto childrenVector = node->GetChildrenNodes();
			for (uint16_t i=0;i<childrenVector.size();++i)
			{							
				nextNodePos.x = std::max(maxWidth , nodePos.x + i* shiftLength);
				RecursivePositionCalculation(childrenVector[i], nextNodePos, nodePos, nodesPos, connectionsPos);
			}		
		};
		RecursivePositionCalculation(startNode, Pos2D{ treePosX,treePosY }, Pos2D{ treePosX,treePosY }, nodesPostitions, connectionsPostitions);
	}

	void Draw()
	{
		if (window)
		{
			for (const auto& nodePos : nodesPostitions)
			{
				sf::CircleShape shape(radius);
				shape.setFillColor(sf::Color::Red);
				shape.setPosition(nodePos.x, nodePos.y);
				window->draw(shape);
			}

			for (const auto& conPos : connectionsPostitions)
			{
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(conPos.first.x + radius, conPos.first.y + radius),sf::Color::Yellow),
					sf::Vertex(sf::Vector2f(conPos.second.x + radius, conPos.second.y + radius),sf::Color::Yellow)
				};
				window->draw(line, 2, sf::Lines);
			}
		}		
	}	
private:	
	std::vector<Pos2D> nodesPostitions;
	std::vector<std::pair<Pos2D,Pos2D>> connectionsPostitions;

	uint16_t radius;
	sf::RenderWindow* window;
	sf::Color color;
};




#endif   // !__TREE_RENDERER_H__