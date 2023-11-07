
#include "librvo2.h"
#include "RVO.h"

#include <assert.h>

void* NewSim() {
	RVO::RVOSimulator *sim = new RVO::RVOSimulator();
  return sim;
}

void FreeSim(void* sim) {
  delete sim;
}

void SimSetTimeStep(void* sim, float interval) {
  assert(sim);
 ((RVO::RVOSimulator*)sim)->setTimeStep(interval);
}

void SimSetAgentDefaults(
  void* sim,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst,
  float radius, float maxSpeed, float vel_x, float vel_y
) {
  assert(sim);
	((RVO::RVOSimulator*)sim)->setAgentDefaults(
    neighborDist, maxNeighbors, timeHorizon, timeHorizonObst, radius, maxSpeed,
    RVO::Vector2(vel_x, vel_y)
  );
}

size_t SimAddAgent(void* sim, float x, float y) {
  assert(sim);
  return ((RVO::RVOSimulator*)sim)->addAgent( RVO::Vector2(x, y));
}

size_t SimAddAgentEx(
  void* sim,
  float x, float y, float radius, float maxSpeed, float vel_x, float vel_y,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst
) {
  assert(sim);
  return ((RVO::RVOSimulator*)sim)->addAgent(
    RVO::Vector2(x, y), neighborDist, maxNeighbors, timeHorizon, timeHorizonObst,
    radius, maxSpeed, RVO::Vector2(vel_x, vel_y)
  );
}

void SimAddObstacle(void* sim, float* vertices, int total) {
  assert(sim);
  std::vector<RVO::Vector2> obs;
  for (int i = 0; i < total; i += 2) {
	  obs.push_back(RVO::Vector2(vertices[i], vertices[i + 1]));
  }
  ((RVO::RVOSimulator*)sim)->addObstacle(obs);;
}

void SimProcessObstacles(void* sim) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->processObstacles();
}

void SimDoStep(void* sim) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->doStep();
}

void SimSetAgentPosition(void* sim, size_t agent_no, float x, float y) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentPosition(agent_no, RVO::Vector2(x, y));
}

void SimSetAgentNeighborDist(void* sim, size_t agent_no, float dist) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentNeighborDist(agent_no, dist);
}

void SimSetAgentMaxSpeed(void* sim, size_t agent_no, float max_speed) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentMaxSpeed(agent_no, max_speed);
}

void SimSetAgentMaxNeighbors(void* sim, size_t agent_no, size_t max_nbs) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentMaxNeighbors(agent_no, max_nbs);
}

void SimSetAgentPrefVelocity(void* sim, size_t agent_no, float vx, float vy) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentPrefVelocity(agent_no, RVO::Vector2(vx, vy));
}

void SimSetAgentRadius(void* sim, size_t agent_no, float radius) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentRadius(agent_no, radius);
}

void SimSetAgentVelocity(void* sim, size_t agent_no, float vx, float vy) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentVelocity(agent_no, RVO::Vector2(vx, vy));
}

void SimSetAgentPosAndVel(void* sim, size_t agent_no, float x, float y, float vx, float vy, float pvx, float pvy) {
  assert(sim);
  ((RVO::RVOSimulator*)sim)->setAgentPosition(agent_no, RVO::Vector2(x, y));
  ((RVO::RVOSimulator*)sim)->setAgentVelocity(agent_no, RVO::Vector2(vx, vy));
  ((RVO::RVOSimulator*)sim)->setAgentPrefVelocity(agent_no, RVO::Vector2(pvx, pvy));
}

size_t SimGetNumAgents(void* sim) {
  assert(sim);
  return ((RVO::RVOSimulator*)sim)->getNumAgents();
}

void SimGetAgentPosition(void* sim, size_t agent_no, float pos[2]) {
  assert(sim);
  RVO::Vector2 v2 = ((RVO::RVOSimulator*)sim)->getAgentPosition(agent_no);
  pos[0] = v2.x(), pos[1] = v2.y();
}

void SimGetAgentPerfVelocity(void* sim, size_t agent_no, float vel[2]) {
  assert(sim);
  RVO::Vector2 v2 = ((RVO::RVOSimulator*)sim)->getAgentPrefVelocity(agent_no);
  vel[0] = v2.x(), vel[1] = v2.y();
}

void SimGetAgentVelocity(void* sim, size_t agent_no, float vel[2]) {
  assert(sim);
  RVO::Vector2 v2 = ((RVO::RVOSimulator*)sim)->getAgentVelocity(agent_no);
  vel[0] = v2.x(), vel[1] = v2.y();
}

void SimGetAgentPosAndVel(void* sim, size_t agent_no, float pos[2], float vel[2]) {
  assert(sim);
  RVO::Vector2 v2 = ((RVO::RVOSimulator*)sim)->getAgentPosition(agent_no);
  pos[0] = v2.x(), pos[1] = v2.y();
  v2 = ((RVO::RVOSimulator*)sim)->getAgentVelocity(agent_no);
  vel[0] = v2.x(), vel[1] = v2.y();
}

