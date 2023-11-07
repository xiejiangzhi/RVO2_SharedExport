
#include "librvo2.h"
#include "RVO.h"

void* NewSim() {
	RVO::RVOSimulator *sim = new RVO::RVOSimulator();
  return sim;
}

void SimSetTimeStep(void* sim, float interval) {
 ((RVO::RVOSimulator*)sim)->setTimeStep(interval);
}

void SimSetAgentDefaults(
  void* sim,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst,
  float radius, float maxSpeed, float vel_x, float vel_y
) {
	((RVO::RVOSimulator*)sim)->setAgentDefaults(
    neighborDist, maxNeighbors, timeHorizon, timeHorizonObst, radius, maxSpeed
  );
}

size_t SimAddAgent(void* sim, float x, float y) {
  return ((RVO::RVOSimulator*)sim)->addAgent( RVO::Vector2(x, y));
}

size_t SimAddAgentEx(
  void* sim,
  float x, float y, float radius, float maxSpeed, float vel_x, float vel_y,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst
) {
  return ((RVO::RVOSimulator*)sim)->addAgent(
    RVO::Vector2(x, y), neighborDist, maxNeighbors, timeHorizon, timeHorizonObst,
    radius, maxSpeed, RVO::Vector2(vel_x, vel_y)
  );
}

void SimAddObstacle(void* sim, float* vertices, int total) {
  std::vector<RVO::Vector2> obs;
  for (int i = 0; i < total; i += 2) {
	  obs.push_back(RVO::Vector2(vertices[i], vertices[i + 1]));
  }
  ((RVO::RVOSimulator*)sim)->addObstacle(obs);;
}

void SimProcessObstacles(void* sim) {
  ((RVO::RVOSimulator*)sim)->processObstacles();
}

void SimDoStep(void* sim) {
  ((RVO::RVOSimulator*)sim)->doStep();
}

void SimSetAgentPosition(void* sim, size_t agent_no, float x, float y) {
  ((RVO::RVOSimulator*)sim)->setAgentPosition(agent_no, RVO::Vector2(x, y));
}

void SimSetAgentNeighborDist(void* sim, size_t agent_no, float dist) {
  ((RVO::RVOSimulator*)sim)->setAgentNeighborDist(agent_no, dist);
}
void SimSetAgentMaxSpeed(void* sim, size_t agent_no, float max_speed) {
  ((RVO::RVOSimulator*)sim)->setAgentMaxSpeed(agent_no, max_speed);
}

void SimSetAgentMaxNeighbors(void* sim, size_t agent_no, size_t max_nbs) {
  ((RVO::RVOSimulator*)sim)->setAgentMaxNeighbors(agent_no, max_nbs);
}

void SimSetAgentPrefVelocity(void* sim, size_t agent_no, float vx, float vy) {
  ((RVO::RVOSimulator*)sim)->setAgentPrefVelocity(agent_no, RVO::Vector2(vx, vy));
}

void SimSetAgentRadius(void* sim, size_t agent_no, float radius) {
  ((RVO::RVOSimulator*)sim)->setAgentRadius(agent_no, radius);
}

void SimSetAgentVelocity(void* sim, size_t agent_no, float vx, float vy) {
  ((RVO::RVOSimulator*)sim)->setAgentVelocity(agent_no, RVO::Vector2(vx, vy));
}

void SimSetAgentPosAndVel(void* sim, size_t agent_no, float x, float y, float vx, float vy, float pvx, float pvy) {
  ((RVO::RVOSimulator*)sim)->setAgentPosition(agent_no, RVO::Vector2(x, y));
  ((RVO::RVOSimulator*)sim)->setAgentVelocity(agent_no, RVO::Vector2(vx, vy));
  ((RVO::RVOSimulator*)sim)->setAgentPrefVelocity(agent_no, RVO::Vector2(pvx, pvy));
}


size_t SimGetNumAgents(void* sim) {
  return ((RVO::RVOSimulator*)sim)->getNumAgents();
}

void SimGetAgentPosition(void* sim, size_t agent_no, float* x, float* y) {
  RVO::Vector2 vel = ((RVO::RVOSimulator*)sim)->getAgentPosition(agent_no);
  *x = vel.x();
  *y = vel.y();
}

void SimGetAgentPerfVelocity(void* sim, size_t agent_no, float* x, float* y) {
  RVO::Vector2 vel = ((RVO::RVOSimulator*)sim)->getAgentPrefVelocity(agent_no);
  *x = vel.x();
  *y = vel.y();
}

void SimGetAgentVelocity(void* sim, size_t agent_no, float* x, float* y) {
  RVO::Vector2 vel = ((RVO::RVOSimulator*)sim)->getAgentVelocity(agent_no);
  *x = vel.x();
  *y = vel.y();
}

