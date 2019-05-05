#include "route_model.h"
#include <iostream>
#include <cmath>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
	int counter = 0;
	// Because RouteModel extends the Model class, when we
	// do this->Nodes we get the Model Nodes.
	for(Model::Node node : this->Nodes()){
		m_Nodes.push_back(RouteModel::Node(counter, this, node));
		counter++;
	}
	CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap(){
	for(const Model::Road &road : Roads()){
		if(road.type != Model::Road::Type::Footway){
			for(int node_idx : Ways()[road.way].nodes){
				if(node_to_road.find(node_idx) == node_to_road.end()){
					node_to_road[node_idx] = std::vector<const Model::Road*> {};
				}
				// Here we are pushing the address. Is not a ref, is the address
				// of the road.
				node_to_road[node_idx].push_back(&road);
			}
		}
	}
}


RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices){
	Node* closest_node = nullptr;
	Node node;
	for(int node_index : node_indices){
	    node = parent_model->SNodes()[node_index];
		// !=0 to avoid returning the node itself.
	    if( this->distance(node) != 0 && !node.visited){
			// We have to dereference the pointer of closest_node
			// We check if the distance of the current node in the for loop is less than
			// The distance of the closest_node that we have so far.
	        if(closest_node == nullptr || this->distance(node) < this->distance(*closest_node)){
		      closest_node = &parent_model->SNodes()[node_index]; // Why not closest_node = &node???¿¿¿
		    }
	    }
    }
	return closest_node;
}



void RouteModel::Node::FindNeighbors(){
	for(auto &road : parent_model->node_to_road[this->index]){
		RouteModel::Node* new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
		// Is posible that the FindNeighbor method
		// returns a nullptr if the current node has no 
		// neighbor nodes that has not been visited.
		if(new_neighbor){
			// Difference between emplace_back and push_back????¡¿¿¿¿¿¿
			this->neighbors.emplace_back(new_neighbor);
		}
	}
}	



RouteModel::Node& RouteModel::FindClosestNode(float x, float y){
	RouteModel::Node node;
	node.x = x;
	node.y = y;
	float min_dist = std::numeric_limits<float>::max();
	float dist;
	int closest_idx;
	for (const auto &road : Roads()){
		if(road.type != Model::Road::Type::Footway){
			for(int node_idx : Ways()[road.way].nodes){
				dist = node.distance(SNodes()[node_idx]);
				if (dist < min_dist){
					closest_idx = node_idx;
					min_dist = dist;
				}
			}
		}
	}
	return SNodes()[closest_idx];
}
