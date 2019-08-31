#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel& model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
  start_x *= 0.01;
	start_y *= 0.01;
	end_x *= 0.01;
	end_y *= 0.01;

  start_node = &m_Model.FindClosestNode(start_x, start_y); 
	end_node = &m_Model.FindClosestNode(end_x, end_y);
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node){
  std::vector<RouteModel::Node> path_found{};
	RoutePlanner::distance = 0.0;
	RouteModel::Node parent;
	while(current_node->parent != nullptr){
		// We need to push back the value.
		path_found.push_back(*current_node);
		parent = *(current_node->parent);
		distance += current_node->distance(parent);
		current_node = current_node->parent;
	}
	path_found.push_back(*current_node);
	distance *= m_Model.MetricScale();
	return path_found;
}


void RoutePlanner::AStarSearch(){
	start_node->visited = true;
	open_list.push_back(start_node);
	RouteModel::Node* current_node = nullptr;
	while(open_list.size() > 0){
    current_node = NextNode();
		if(current_node->distance(*end_node) == 0){
			m_Model.path = ConstructFinalPath(current_node);
			return;
		}
		AddNeighbors(current_node);
	}
}


float RoutePlanner::CalculateHValue(const RouteModel::Node* node){
  return node->distance(*end_node);
}


RouteModel::Node* RoutePlanner::NextNode(){
  std::sort(open_list.begin(), open_list.end(), [](const auto &_1st, const auto &_2nd){
			return _1st->h_value + _1st->g_value < _2nd->h_value + _2nd->g_value;
			});
	RouteModel::Node* lowest_node = open_list.front();
	open_list.erase(open_list.begin());
	return lowest_node;
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node){
  current_node->FindNeighbors(); 
  for(auto& neighbor : current_node->neighbors){
		neighbor->parent = current_node;
		neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
		neighbor->h_value = CalculateHValue(neighbor);

		open_list.push_back(neighbor);
		neighbor->visited = true;
	}
}
