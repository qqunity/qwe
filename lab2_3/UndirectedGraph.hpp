#ifndef LAB2_3_UNDIRECTEDGRAPH_HPP
#define LAB2_3_UNDIRECTEDGRAPH_HPP

#include "IDictionary.hpp"
#include "AVLTreeDictionary.hpp"
#include "BTreeDictionary.hpp"
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include "Pair.hpp"

namespace graph {
    template<typename N>
    struct Node {
        N node{};
        sequence::Sequence<Node<N> *> *nodesPtr;
    };

    template<typename L, typename N>
    class UndirectedGraph {
    private:
        unsigned int edgesQuantity{};
        unsigned int nodesQuantity{};
        L defaultLabel;
        N defaultNode;
        std::string baseTypeOfSequence;
        dictionary::IDictionary<N, Node<N> *> *nodes;
        std::map<std::pair<N, N>, L> edges;
    protected:
        bool dfs(N node1, N node2, sequence::Sequence<N> *visitedNodes);

        unsigned int checkConnected(N node, sequence::Sequence<N> *visitedNodes);
    public:
        UndirectedGraph(const std::string& baseTypeOfDictionary, const std::string& baseTypeOfSequence, L defaultLabel, N defaultNode);

        void addNode(N node);

        void addEdge(N node1, N node2, L label);

        unsigned int degreeOfNode(N node);

        sequence::SequenceIterator<Pair<N, L>> neighbours(N node);

        bool isNode(N node);

        bool isNeighbours(N node1, N node2);

        bool checkPath(N node1, N node2);

        unsigned int getNodesQuantity();

        bool isConnected();

        L getLabel(N node1, N node2);

        void removeNode(N node);

        sequence::SequenceIterator<N> getNodes();

        std::map<std::pair<N, N>, L> getEdges();

        void removeEdge(N node1, N node2);

        void printGraph(N node, sequence::Sequence<Pair<N, N>> *passedEdges);

        std::string toString();

        template<typename L1, typename  N1>
        friend std::ostream &operator<<(std::ostream &out, UndirectedGraph<L1, N1> &graph);
    };

    template<typename L, typename N>
    UndirectedGraph<L, N>::UndirectedGraph(const std::string& baseTypeOfDictionary, const std::string& baseTypeOfSequence,
                                           L defaultLabel, N defaultNode) {
        this->edgesQuantity = 0;
        this->nodesQuantity = 0;
        this->defaultNode = defaultNode;
        this->defaultLabel = defaultLabel;
        this->baseTypeOfSequence = baseTypeOfSequence;
        auto node = new Node<N>;
        node->node = this->defaultNode;
        node->nodesPtr = nullptr;
        if (baseTypeOfDictionary == "AVLTreeDictionary") {
            this->nodes = new dictionary::AVLTreeDictionary<N, Node<N> *>(baseTypeOfSequence, this->defaultNode,
                                                                             node);
        } else if (baseTypeOfDictionary == "BTreeDictionary") {
            this->nodes = new dictionary::BTreeDictionary<N, Node<N> *>(2, baseTypeOfSequence, this->defaultNode,
                                                                           node);
        } else {
            throw exceptions::UndirectedGraphException("Invalid dictionary type!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    void UndirectedGraph<L, N>::addNode(N node) {
        if (!this->nodes->contains(node)) {
            auto newNode = new Node<N>;
            newNode->node = node;
            if (this->baseTypeOfSequence == "ArraySequence") {
                newNode->nodesPtr = new array::ArraySequence<Node<N> *>();
            } else {
                newNode->nodesPtr = new list::LinkedListSequence<Node<N> *>();
            }
            this->nodes->insert(node, newNode);
            ++this->nodesQuantity;
        }

    }

    template<typename L, typename N>
    void UndirectedGraph<L, N>::addEdge(N node1, N node2, L label) {
        if (this->isNeighbours(node1, node2)) {
            throw exceptions::UndirectedGraphException("Edge has already exist!", __LINE__, __FILE__);
        }
        if (this->nodes->contains(node1) && this->nodes->contains(node2)) {
            if (node1 == node2) {
                this->edges[std::make_pair(node1, node2)] =  label;
                Node<N> *node1Ptr = this->nodes->get(node1).getValue();
                node1Ptr->nodesPtr->append(node1Ptr);
            } else {
                this->edges[std::make_pair(node1, node2)] =  label;
                Node<N> *node1Ptr = this->nodes->get(node1).getValue();
                Node<N> *node2Ptr = this->nodes->get(node2).getValue();
                node1Ptr->nodesPtr->append(node2Ptr);
                node2Ptr->nodesPtr->append(node1Ptr);
            }
            ++this->edgesQuantity;
        } else {
            throw exceptions::UndirectedGraphException("Some node doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L1, typename N1>
    std::ostream &operator<<(std::ostream &out, UndirectedGraph<L1, N1> &graph) {
        for (auto edgesItems: graph.edges) {
            out << edgesItems.first.first << "<->" << edgesItems.first.second << " label: " << edgesItems.second << '\n';
        }
        return out;
    }

    template<typename L, typename N>
    unsigned int UndirectedGraph<L, N>::degreeOfNode(N node) {
        if (this->nodes->contains(node)) {
            return this->nodes->get(node).getValue()->nodesPtr->length();
        } else {
            throw exceptions::UndirectedGraphException("Node doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    sequence::SequenceIterator<Pair<N, L>> UndirectedGraph<L, N>::neighbours(N node) {
        if (this->nodes->contains(node)) {
            sequence::Sequence<Pair<N, L>> *neighbours;
            if (this->baseTypeOfSequence == "ArraySequence") {
                neighbours = new array::ArraySequence<Pair<N, L>>();
            } else {
                neighbours = new list::LinkedListSequence<Pair<N, L>>();
            }
            auto nodesPtr = this->nodes->get(node).getValue()->nodesPtr;
            for (unsigned int i = 0; i < nodesPtr->length(); ++i) {
                if (this->edges.contains(std::make_pair(node, nodesPtr->getElement(i)->node))){
                    neighbours->append(Pair(std::pair(nodesPtr->getElement(i)->node, this->edges[std::make_pair(node, nodesPtr->getElement(i)->node)])));
                } else {
                    neighbours->append(Pair(std::pair(nodesPtr->getElement(i)->node, this->edges[std::make_pair(nodesPtr->getElement(i)->node, node)])));

                }
            }
            return sequence::SequenceIterator<Pair<N, L>>(neighbours);
        } else {
            throw exceptions::UndirectedGraphException("Node doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    bool UndirectedGraph<L, N>::isNeighbours(N node1, N node2) {
        return this->edges.contains(std::make_pair(node1, node2)) || this->edges.contains(std::make_pair(node2, node1));
    }

    template<typename L, typename N>
    L UndirectedGraph<L, N>::getLabel(N node1, N node2) {
        if (this->isNeighbours(node1, node2)) {
            if (this->edges.contains(std::make_pair(node1, node2))) {
                return this->edges[std::make_pair(node1, node2)];
            } else {
                return this->edges[std::make_pair(node2, node1)];
            }
        } else {
            throw exceptions::UndirectedGraphException("Edge doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    void UndirectedGraph<L, N>::removeNode(N node) {
        if (this->nodes->contains(node)) {
            Node<N> *nodeValue = this->nodes->get(node).getValue();
            for (auto  neighbour: this->neighbours(node)) {
                Node<N> *neighbourValue = this->nodes->get(neighbour.getValue().getFirst()).getValue();
                this->removeEdge(node, neighbourValue->node);
            }
            this->nodes->remove(node);
            --this->nodesQuantity;
        } else {
            throw exceptions::UndirectedGraphException("Node doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    void UndirectedGraph<L, N>::removeEdge(N node1, N node2) {
        if (this->edges.contains(std::make_pair(node1, node2)) || this->edges.contains(std::make_pair(node2, node1))) {
            if (node1 == node2) {
                Node<N> *node1Value = this->nodes->get(node1).getValue();
                Node<N> *node2Value = this->nodes->get(node2).getValue();
                node1Value->nodesPtr->pop(node1Value->nodesPtr->getIndex(node2Value));
                this->edges.erase(std::make_pair(node1, node2));
            } else {
                Node<N> *node1Value = this->nodes->get(node1).getValue();
                Node<N> *node2Value = this->nodes->get(node2).getValue();
                node1Value->nodesPtr->pop(node1Value->nodesPtr->getIndex(node2Value));
                node2Value->nodesPtr->pop(node2Value->nodesPtr->getIndex(node1Value));
                if (this->edges.contains(std::make_pair(node1, node2))) {
                    this->edges.erase(std::make_pair(node1, node2));
                } else {
                    this->edges.erase(std::make_pair(node2, node1));
                }
            }
            --this->edgesQuantity;
        } else {
            throw exceptions::UndirectedGraphException("Edge doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    void UndirectedGraph<L, N>::printGraph(N node, sequence::Sequence<Pair<N, N>> *passedEdges) {
        if (this->nodes->contains(node)) {
            Node<N> *nodeValue = this->nodes->get(node).getValue();
            if (nodeValue->nodesPtr->length() != 0) {
                for (auto  neighbour: this->neighbours(node)) {
                    Node<N> *neighbourValue = this->nodes->get(neighbour.getValue().getFirst()).getValue();
                    if (passedEdges->getIndex(Pair(node, neighbourValue->node)) == -1 && passedEdges->getIndex(Pair(neighbourValue->node, node)) == -1) {
                        std::cout << node << "<->" << neighbourValue->node << '\n';
                        passedEdges->append(Pair(node, neighbourValue->node));
                        this->printGraph(neighbourValue->node, passedEdges);
                    }
                }
            }
        } else {
            throw exceptions::UndirectedGraphException("Node doesn't exist!", __LINE__, __FILE__);
        }
    }

    template<typename L, typename N>
    bool UndirectedGraph<L, N>::isNode(N node) {
        return this->nodes->contains(node);
    }

    template<typename L, typename N>
    bool UndirectedGraph<L, N>::dfs(N node1, N node2, sequence::Sequence<N> *visitedNodes) {
        if (node1 == node2) {
            return true;
        }
        visitedNodes->append(node1);
        for (auto neighbour: this->neighbours(node1)) {
            if (visitedNodes->getIndex(neighbour.getValue().getFirst()) == -1) {
                if (this->dfs(neighbour.getValue().getFirst(), node2, visitedNodes)) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename L, typename N>
    bool UndirectedGraph<L, N>::checkPath(N node1, N node2) {
        if (!this->nodes->contains(node1) || !this->nodes->contains(node2)) {
            throw exceptions::UndirectedGraphException("Some node doesn't exist!", __LINE__, __FILE__);
        }
        sequence::Sequence<N> *visitedNodes;
        if (this->baseTypeOfSequence == "ArraySequence") {
            visitedNodes =  new array::ArraySequence<N>();
        } else {
            visitedNodes = new list::LinkedListSequence<N>();
        }
        return this->dfs(node1, node2, visitedNodes);
    }

    template<typename L, typename N>
    unsigned int UndirectedGraph<L, N>::checkConnected(N node, sequence::Sequence<N> *visitedNodes) {
        unsigned int visitedNodesQuantity = 1;
        visitedNodes->append(node);
        for (auto neighbour: this->neighbours(node)) {
            if (visitedNodes->getIndex(neighbour.getValue().getFirst()) == -1) {
                visitedNodesQuantity += this->checkConnected(neighbour.getValue().getFirst(), visitedNodes);
            }
        }
        return visitedNodesQuantity;
    }

    template<typename L, typename N>
    bool UndirectedGraph<L, N>::isConnected() {
        N someNode = *this->nodes->keys().begin();
        sequence::Sequence<N> *visitedNodes;
        if (this->baseTypeOfSequence == "ArraySequence") {
            visitedNodes =  new array::ArraySequence<N>();
        } else {
            visitedNodes = new list::LinkedListSequence<N>();
        }
        return this->checkConnected(someNode, visitedNodes) == this->nodes->length();
    }

    template<typename L, typename N>
    unsigned int UndirectedGraph<L, N>::getNodesQuantity() {
        return this->nodesQuantity;
    }

    template<typename L, typename N>
    sequence::SequenceIterator<N> UndirectedGraph<L, N>::getNodes() {
        return this->nodes->keys();
    }

    template<typename L, typename N>
    std::map<std::pair<N, N>, L> UndirectedGraph<L, N>::getEdges() {
        return this->edges;
    }

    template<typename L, typename N>
    std::string UndirectedGraph<L, N>::toString() {
        std::string graphRepresentation;
        for (auto edgesItems: this->edges) {
            graphRepresentation += edgesItems.first.first + "<->" + edgesItems.first.second + " label: " + std::to_string(edgesItems.second) + "\n";
        }
        return graphRepresentation;
    }
}
#endif
