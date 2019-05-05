#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
	float GetDistance() const {return distance;}
	void AStarSearch();

  private:
    // Add private variables or methods declarations here.
    RouteModel &m_Model;
	RouteModel::Node* start_node;
	RouteModel::Node* end_node;
	float distance;
	// why a vector of nodes instead of node pointers?
	// The answer is that because we are not operating in those nodes any
	// longer. But i don't understand this.
	std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node*);
	float CalculateHValue(const RouteModel::Node* node);
	std::vector<RouteModel::Node*> open_list;
	RouteModel::Node* NextNode();
	void AddNeighbors(RouteModel::Node* current_node);
};
