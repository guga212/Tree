#ifndef  __NODE_H__
#define __NODE_H__

#include <string>
#include <sstream>
#include <string_view>
#include <functional>
#include <algorithm>
#include <memory>
#include <vector>
#include <set>

template <class T>
 class Node : public std::enable_shared_from_this<Node<T>>
{
public:
	using NodeSharedPtr = std::shared_ptr<Node<T>>;
	using NodeWeakPtr = std::weak_ptr<Node<T>>;

	static NodeSharedPtr CreateRootNode(const T& v)
	{
		return std::shared_ptr<Node<T>>(new Node<T>(v,"0"));
	}
	static NodeSharedPtr CreateRootNode(T&& v)
	{
		return std::shared_ptr<Node<T>>(new Node<T>(v,"0"));
	}
public:	
	NodeSharedPtr CreateChildNode(T v)
	{		
		auto ChildName = objectName+std::string("_")+std::to_string(sortedChildren.size() + 1);
		auto childSharedPtr = std::shared_ptr<Node<T>>(new Node<T>(v, ChildName));
		childSharedPtr->parentNode = this->shared_from_this();
		sortedChildren.insert(childSharedPtr);		
		return childSharedPtr;
	}

	std::vector<NodeSharedPtr> GetChildrenNodes()
	{
		return std::vector(sortedChildren.begin(), sortedChildren.end());
	}	
	NodeSharedPtr GetParentNode()
	{
		return parentNode.lock();
	}

	T GetValue() { return value; }	
	std::string GetNodeName() { return this->objectName; }

	void Serialize(std::string& str)
	{
		NodeSharedPtr RootNode = this->shared_from_this();		
		while (RootNode->GetParentNode())
			RootNode=RootNode->GetParentNode();

		std::function<void(NodeSharedPtr node, std::string& str)> RecursiveSerialize;
		RecursiveSerialize = [&RecursiveSerialize](NodeSharedPtr node, std::string& str)
		{	
			std::stringstream valueStream;
			valueStream << node->GetValue();
			str += std::string("[") + valueStream.str() + std::string(";") + node->GetNodeName() + std::string("]");
			auto childrenVector=node->GetChildrenNodes();			
			for(auto& childNode:childrenVector)
				RecursiveSerialize(childNode, str);			
			str += std::string_view("#");
		};

		RecursiveSerialize(RootNode, str);
	}

	template <class V> 
	bool operator < (V el)
	{
		return value < el;
	}	
	bool operator < (Node<T>& node)
	{
		return value < node.GetValue();
	}
protected:
	Node(const T& v, std::string_view name) :value(v), objectName(name) {}
	Node(T&& v, std::string_view name) :value(v), objectName(name) {}
	Node(const Node<T>&) = delete;
	Node(Node<T>&&) = delete;

	std::multiset<NodeSharedPtr, bool(*)(const NodeSharedPtr&, const NodeSharedPtr&)> 
		sortedChildren{ [](const NodeSharedPtr& lhs, const NodeSharedPtr& rhs) { return *lhs<*rhs; } };
	NodeWeakPtr parentNode;
	T value;
	std::string objectName;
};




#endif // ! __NODE_H__
