#ifndef __TEST_NODE_H__
#define __TEST_NODE_H__
#include "Node.h"

#include <iostream>
#include <cassert>
#include <map>

template <class T>
class TestNode
{
public:

	static void RunAllTest()
	{
		CreateRootNode_Lvalue_Test_CreationFail();
		CreateRootNode_Rvalue_Test_CreationFail();
		CreateChildNode_Test_MemoryManagement();
		GetChildrenNodes_Test_ReturnIdentity();
		GetParent_Test_ReturnIdentity();
		GetValue_Test_ReturnEquality();
		GetNodeName_Test_NameUnique();
		Serialize_Test_DataCorrectSave();
		Serialize_Test_StructureCorrectness();
		LessCompareOperator_Test_ComparsionCorrectness();
	}

	static void CreateRootNode_Lvalue_Test_CreationFail()
	{
		uint16_t testIterationsMax = 100;
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			T val{};
			auto rootPtr = Node<T>::CreateRootNode(val);
			assert(rootPtr);
		}
		std::cout<<"Test of the CreateRootNode(lvalue) at creation fail: PASSED."<<std::endl;
	}

	static void CreateRootNode_Rvalue_Test_CreationFail()
	{
		auto ReturnValue = []() { T val{}; return val; };

		uint16_t testIterationsMax = 100;
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{						
			auto rootPtr = Node<T>::CreateRootNode(ReturnValue());
			assert(rootPtr);
		}
		std::cout << "Test of the CreateRootNode(rvalue) at creation fail: PASSED." << std::endl;
	}

	static void CreateChildNode_Test_MemoryManagement()
	{
		uint16_t testIterationsMax = 60;
		auto ReturnValue = []() { T val{}; return val; };
		
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			std::weak_ptr<Node<T>> nodeReferenceCountKeeper_1;
			std::weak_ptr<Node<T>> nodeReferenceCountKeeper_2;
			std::weak_ptr<Node<T>> nodeReferenceCountKeeper_3;
			{
				T val{};
				auto nodePtr_1 = Node<T>::CreateRootNode(val); 
				assert(nodePtr_1);
				auto nodePtr_2 = nodePtr_1->CreateChildNode(ReturnValue());
				assert(nodePtr_2);
				auto nodePtr_3 = nodePtr_1->CreateChildNode(ReturnValue());
				assert(nodePtr_3);

				nodeReferenceCountKeeper_1 = nodePtr_2;
				assert(nodeReferenceCountKeeper_1.use_count() != 0);

				for (uint16_t j = 0; j < (i + 5); ++j)
				{
					T localVal{};
					auto nodeLocalPtr_1 = nodePtr_1->CreateChildNode(ReturnValue());
					auto nodeLocalPtr_2 = nodePtr_2->CreateChildNode(localVal);
					auto nodeLocalPtr_3 = nodePtr_3->CreateChildNode(localVal);

					nodeReferenceCountKeeper_2 = nodeLocalPtr_3;
					assert(nodeReferenceCountKeeper_2.use_count() != 0);

					nodeReferenceCountKeeper_3 = nodeLocalPtr_1;
					assert(nodeReferenceCountKeeper_3.use_count() != 0);
				}
			}
			assert(nodeReferenceCountKeeper_1.use_count() == 0);
			assert(nodeReferenceCountKeeper_2.use_count() == 0);
			assert(nodeReferenceCountKeeper_3.use_count() == 0);
		}
		std::cout << "Test of the CreateChildNode at memory managment: PASSED." << std::endl;
	}

	static void GetChildrenNodes_Test_ReturnIdentity()
	{
		uint16_t testIterationsMax = 10;
		auto ReturnValue = []() { T val{}; return val; };

		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{	
			T val{};
			auto rootNode = Node<T>::CreateRootNode(val);
			std::vector<std::shared_ptr<Node<T>>> childrenVec;
			assert(rootNode);

			uint8_t childNmbMult = 10;
			for (uint16_t j = 0; j < childNmbMult*(i+1); ++j)
			{
				auto childNode=rootNode->CreateChildNode(ReturnValue());
				assert(childNode);
				childrenVec.push_back(childNode);				
			}
			auto rootChildrenVec=rootNode->GetChildrenNodes();
			assert(rootChildrenVec.size() == childrenVec.size());
			for (auto i=rootChildrenVec.begin();i!=rootChildrenVec.end();++i)
			{
				auto findResult=std::find(childrenVec.begin(), childrenVec.end(), *i);
				assert(findResult != childrenVec.end());
			}		
		}		
		
		std::cout << "Test of the GetChildrenNodes at returned nodes identity correctness: PASSED." << std::endl;
	}

	static void GetParent_Test_ReturnIdentity()
	{
		uint16_t testIterationsMax = 10;
		auto ReturnValue = []() { T val{}; return val; };

		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			T val{};
			auto rootNode = Node<T>::CreateRootNode(val);
			std::vector<std::shared_ptr<Node<T>>> childrenVec;
			assert(rootNode);

			uint8_t childNmbMult = 10;
			for (uint16_t j = 0; j < childNmbMult*(i + 1); ++j)
			{
				auto childNode = rootNode->CreateChildNode(ReturnValue());
				assert(childNode);
				childrenVec.push_back(childNode);
			}
						
			for (auto i = childrenVec.begin(); i != childrenVec.end(); ++i)
			{				
				assert((*i)->GetParentNode() == rootNode);
			}
		}

		std::cout << "Test of the GetParentNodes at returned nodes identity correctness: PASSED." << std::endl;
	}

	static void GetValue_Test_ReturnEquality()
	{
		uint16_t testIterationsMax = 100;
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			T val {};
			auto rootPtr = Node<T>::CreateRootNode(val);
			assert(rootPtr);
			assert(val == rootPtr->GetValue());
			auto childPtr = rootPtr->CreateChildNode(std::move(val));
			assert(childPtr);
			assert(val == childPtr->GetValue());
		}
		std::cout << "Test of the GetValue at correctness of the return: PASSED." << std::endl;
	}

	static void GetNodeName_Test_NameUnique()
	{ 
		uint16_t testIterationsMax = 60;		
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			std::vector<std::string> nameVec;
			T val{};

			auto rootPtr = Node<T>::CreateRootNode(val);
			assert(rootPtr);
			nameVec.push_back(rootPtr->GetNodeName());
			auto childPtr = rootPtr->CreateChildNode(val);
			assert(childPtr);
			nameVec.push_back(childPtr->GetNodeName());
			
			for (uint16_t i = 0; i < testIterationsMax; ++i)
			{
				auto localChildPtr_1 = rootPtr->CreateChildNode(val);
				assert(localChildPtr_1);
				nameVec.push_back(localChildPtr_1->GetNodeName());
				auto localChildPtr_2 = childPtr->CreateChildNode(val);
				assert(localChildPtr_2);
				nameVec.push_back(localChildPtr_2->GetNodeName());
			}
			auto sizeBeforeCopyErase = nameVec.size();
			std::unique(nameVec.begin(), nameVec.end());
			auto sizeAfterCopyErase = nameVec.size();
			assert(sizeAfterCopyErase == sizeBeforeCopyErase);
		}
		std::cout << "Test of the GetNodeName at uniqueness of the name: PASSED." << std::endl;
	}

	static void Serialize_Test_DataCorrectSave()
	{		
		uint16_t testIterationsMax = 60;
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			std::vector<std::string> nameVec;
			T val{};

			auto rootPtr = Node<T>::CreateRootNode(val);
			assert(rootPtr);
			nameVec.push_back(rootPtr->GetNodeName());
			auto childPtr = rootPtr->CreateChildNode(val);
			assert(childPtr);
			nameVec.push_back(childPtr->GetNodeName());

			for (uint16_t i = 0; i < testIterationsMax; ++i)
			{
				auto localChildPtr_1 = rootPtr->CreateChildNode(val);
				assert(localChildPtr_1);
				nameVec.push_back(localChildPtr_1->GetNodeName());
				auto localChildPtr_2 = childPtr->CreateChildNode(val);
				assert(localChildPtr_2);
				nameVec.push_back(localChildPtr_2->GetNodeName());
			}
			
			std::string rootSerializedData;
			rootPtr->Serialize(rootSerializedData);
			std::string childSerializedData;
			childPtr->Serialize(childSerializedData);
			assert(rootSerializedData == childSerializedData);

			for (const auto& name : nameVec)
			{
				auto result=rootSerializedData.find(name);				
				assert(result != std::string::npos);
			}
		}
		std::cout << "Test of the Serialize at data correct save: PASSED." << std::endl;
	}

	static void Serialize_Test_StructureCorrectness()
	{
		uint16_t testIterationsMax = 30;
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{			
			T val{};

			auto rootPtr = Node<T>::CreateRootNode(val);
			assert(rootPtr);
		
			auto childPtr = rootPtr->CreateChildNode(val);
			assert(childPtr);
		
			for (uint16_t i = 0; i < testIterationsMax; ++i)
			{
				auto localChildPtr_1 = rootPtr->CreateChildNode(val);
				assert(localChildPtr_1);		
				auto localChildPtr_2 = childPtr->CreateChildNode(val);
				assert(localChildPtr_2);				
			}

			std::string rootSerializedData;
			rootPtr->Serialize(rootSerializedData);			

			auto controllNode=rootPtr;
			uint16_t currentLevel = 0;
			std::map<uint16_t, uint16_t> levelCurrentChild{ {0,0} };

			for (const auto& c : rootSerializedData)
			{				
				if (c == '[')
				{
					assert(controllNode);
					auto childVec=controllNode->GetChildrenNodes();

					if (childVec.size() > levelCurrentChild[currentLevel])
					{
						controllNode = childVec[levelCurrentChild[currentLevel]];
						levelCurrentChild[currentLevel+1]++;
					}

					
					currentLevel++;
				}

				if (c == '#')
				{
					controllNode = controllNode->GetParentNode();
					--currentLevel;					
				}
			}
		}
		std::cout << "Test of the Serialize at data correct save: PASSED." << std::endl;
	}

	static void LessCompareOperator_Test_ComparsionCorrectness()
	{
		uint16_t testIterationsMax = 100;
		for (uint16_t i = 0; i < testIterationsMax; ++i)
		{
			T v1{}; T v2{};
			auto node1 = Node<T>::CreateRootNode(v1);
			auto node2 = Node<T>::CreateRootNode(v2);
			assert((v1 < v2) == (*node1 < *node2));
		}
		std::cout << "Test of the operator < at comparsion correctness: PASSED." << std::endl;
	}	
};


#endif // !__TEST_NODE_H__
