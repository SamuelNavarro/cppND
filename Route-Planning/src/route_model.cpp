#include "route_model.h"
#include <iostream>


RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  int counter = 0;
	for(Model::Node _node : this->Nodes()){
		m_Nodes.push_back(RouteModel::Node(counter, this, _node));
		counter += 1;
	}
	CreateNodeToRoadHashmap();
}


void RouteModel::CreateNodeToRoadHashmap(){
	for(const Model::Road& road : Roads()){
		if(road.type != Model::Road::Type::Footway){
			for(auto const node_idx : Ways()[road.way].nodes){
				if(node_to_road.find(node_idx) == node_to_road.end()){
					node_to_road[node_idx] = std::vector<const Model::Road*>{};
				}
				// We give the addres  with & 
				node_to_road[node_idx].push_back(&road);
			}
		}
	}
}


RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices){
	RouteModel::Node* closest_node = nullptr;	
	RouteModel::Node node;
	for(int node_index : node_indices){
		node = parent_model->SNodes()[node_index];
		if(distance(node) != 0 && !node.visited){
			if(closest_node == nullptr || this->distance(node) < this->distance(*closest_node)){
				closest_node = &parent_model->SNodes()[node_index];
			}
		}

	}
	return closest_node;
};



void RouteModel::Node::FindNeighbors(){
  for(auto& road : parent_model->node_to_road[this->index]){
		std::vector<int> node_indices = parent_model->Ways()[road->way].nodes;
		RouteModel::Node* node = FindNeighbor(node_indices);
		if(node != nullptr){
			this->neighbors.push_back(node);
		}
	}
}


RouteModel::Node& RouteModel::FindClosestNode(float x, float y){
	RouteModel::Node tmp_node;
	tmp_node.x = x;
	tmp_node.y = y;
	float dst;

  float min_dist = std::numeric_limits<float>::max();
	int closest_idx;
	for(const Model::Road& road : Roads()){
		if(road.type != Model::Road::Type::Footway){
			for(int node_idx : Ways()[road.way].nodes){
        dst = tmp_node.distance(SNodes()[node_idx]);
				if(dst < min_dist){
					closest_idx = node_idx;
					min_dist = dst;
				}
			}
		}
	}
	return SNodes()[closest_idx];
}









