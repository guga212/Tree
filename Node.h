#ifndef  __TREE_H__

#include <cassert>
#include <string>
#include <string_view>
#include <algorithm>
#include <memory>
#include <vector>
#include <set>

template <class T>
class NodesCommonDataStorage
{
protected:
	NodesCommonDataStorage()
	{
		objectName = std::string("Node_") + GetNodeId();

		if ( (nodeIdKeeper.size() > nodeIdKeeperMaxSize) || ( (nodeIdKeeper.size() == nodeIdKeeperMaxSize) && (nodeIdKeeper.back() == UINT64_MAX) ) )
		{
			nodeIdKeeper.clear();

			bool NodesCountLessThanNodesMaxSize = false;
			assert(NodesCountLessThanNodesMaxSize);						
		}

		if (nodeIdKeeper.back() == UINT64_MAX)
			nodeIdKeeper.push_back(0);

		nodeIdKeeper.back()++;		
	}
	NodesCommonDataStorage(const NodesCommonDataStorage&) = delete;
	NodesCommonDataStorage(NodesCommonDataStorage&&) = delete;
	std::string GetNodeId()
	{
		std::string nodeId;
		
		for (const auto& el : nodeIdKeeper)
			nodeId += std::to_string(el);

		return nodeId;
	}
	std::string objectName;
private:
	static std::vector<uint64_t> nodeIdKeeper;
	static uint8_t nodeIdKeeperMaxSize;
};
template <typename T>
uint8_t NodesCommonDataStorage<T>::nodeIdKeeperMaxSize = 8;
template <typename T>
std::vector<uint64_t> NodesCommonDataStorage<T>::NodesCommonDataStorage::nodeIdKeeper{ 0 };


template <class T>
 class Node : public NodesCommonDataStorage<Node<T>>, public std::enable_shared_from_this<Node<T>>
{
public:
	using NodeSharedPtr = std::shared_ptr<Node<T>>;
	using NodeWeakPtr = std::weak_ptr<Node<T>>;

	~Node() { std::cout << "Node destructor.\n"; }

	T GetValue() { return value; }
	std::string GetNodeName() { return this->objectName; }

	void SetParent(NodeSharedPtr np)
	{
		parentNode.reset();
		parentNode = np;
	}
	const NodeSharedPtr GetParent()
	{
		return parentNode.lock();
	}

	void AddChildNode(NodeSharedPtr np)
	{	
		if(np)
		{
			np->SetParent(this->shared_from_this());
			sortedChildren.insert(np);
		}
	}
	NodeSharedPtr GetChildNode(std::string_view str) 
	{
		auto result=std::find_if(sortedChildren.begin(), sortedChildren.end(), [str](NodeSharedPtr el) { return str.compare(el->GetNodName()) == 0; });
		if (result != sortedChildren.end())
			return *result;
		return nullptr;
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

	template <class V>
	bool operator > (V el)
	{
		return value > el;
	}
	bool operator > (Node<T>& node)
	{
		return value > node.GetValue();
	}

	template <class V>
	bool operator <= (V el)
	{
		return value <= el;
	}
	bool operator <= (Node<T>& node)
	{
		return value <= node.GetValue();
	}

	template <class V>
	bool operator >= (V el)
	{
		return value >= el;
	}
	bool operator >= (Node<T>& node)
	{
		return value >= node.GetValue();
	}

	template <class V>
	bool operator == (V el)
	{
		return value == el;
	}
	bool operator == (Node<T>& node)
	{
		return value == node.GetValue();
	}

	template <class V>
	bool operator != (V el)
	{
		return value != el;
	}
	bool operator != (Node<T>& node)
	{
		return value != node.GetValue();
	}

public:
	static NodeSharedPtr CreateNode(const T& v, NodeSharedPtr parent = nullptr)
	{		
		return std::shared_ptr<Node<T>>(new Node<T>(v, parent));
	}
	static NodeSharedPtr CreateNode(T&& v, NodeSharedPtr parent = nullptr)
	{
		return std::shared_ptr<Node<T>>(new Node<T>(v, parent));
	}
protected:
	Node(const T& v, NodeSharedPtr parent) :value(v), parentNode(parent) {}
	Node(T&& v, NodeSharedPtr parent) :value(v), parentNode(parent) {}
	Node(const Node<T>&) = delete;
	Node(Node<T>&&) = delete;
	
	std::multiset<NodeSharedPtr, bool(*)(const NodeSharedPtr&, const NodeSharedPtr&)> 
		sortedChildren{ [](const NodeSharedPtr& lhs, const NodeSharedPtr& rhs) { return *lhs<*rhs; } };
	NodeWeakPtr parentNode;
	T value;
};




#endif // ! __TREE_H__
