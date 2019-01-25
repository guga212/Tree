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
		std::function<void(std::shared_ptr<Node<T>> node, Pos2D nodePos, Pos2D parentPos, std::vector<std::pair<std::string, Pos2D>>& nodesValuesPositions, std::vector<std::pair<Pos2D, Pos2D>>& connectionsPos)> RecursivePositionCalculation;
		float maxWidth = 0;
		float shiftLength = 3.5f*r;

		RecursivePositionCalculation = [&RecursivePositionCalculation,&maxWidth,&shiftLength](std::shared_ptr<Node<T>> node, Pos2D nodePos, Pos2D parentPos, std::vector<std::pair<std::string, Pos2D>>& nodesValuesPositions, std::vector<std::pair<Pos2D, Pos2D>>& connectionsPos)
		{	
			maxWidth = std::max(maxWidth, nodePos.x);
			std::stringstream valueStream; valueStream << node->GetValue();
			nodesValuesPositions.push_back({ valueStream.str(), nodePos });
			connectionsPos.push_back({ parentPos, nodePos });			
			Pos2D nextNodePos { nodePos.x, nodePos.y + shiftLength };

			auto childrenVector = node->GetChildrenNodes();
			for (uint16_t i=0;i<childrenVector.size();++i)
			{						
				if (maxWidth > nodePos.x + shiftLength * i)			
					nextNodePos.x = maxWidth + shiftLength;				
				else				
					nextNodePos.x = nodePos.x + shiftLength * i;

				RecursivePositionCalculation(childrenVector[i], nextNodePos, nodePos, nodesValuesPositions, connectionsPos);
			}		
		};
		RecursivePositionCalculation(startNode, Pos2D{ treePosX,treePosY }, Pos2D{ treePosX,treePosY }, nodesValuePostitions, connectionsPostitions);
		
		font.loadFromFile("arial.ttf")
	}

	void Draw()
	{
		if (window)
		{
			for (const auto& nodeValuePos : nodesValuePostitions)
			{
				sf::CircleShape shape(radius);
				shape.setFillColor(sf::Color::Red);
				shape.setPosition(nodeValuePos.second.x, nodeValuePos.second.y);
				window->draw(shape);			
				
				sf::Text valueText;				
				valueText.setFont(font);
				valueText.setPosition(nodeValuePos.second.x + 0.5*radius, nodeValuePos.second.y + 0.5*radius);
				valueText.setString(nodeValuePos.first.c_str());
				valueText.setCharacterSize(radius);
				valueText.setFillColor(sf::Color::Green);									
				window->draw(valueText);
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
	std::vector<std::pair<std::string, Pos2D>> nodesValuePostitions;
	std::vector<std::pair<Pos2D,Pos2D>> connectionsPostitions;

	uint16_t radius;
	sf::RenderWindow* window;		
	sf::Font font;
};




#endif   // !__TREE_RENDERER_H__