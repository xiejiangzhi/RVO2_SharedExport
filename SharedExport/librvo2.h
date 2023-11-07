#define API __declspec(dllexport)

#include <cstddef>

extern "C" {

API void* NewSim();
API void FreeSim(void* sim);
API void SimSetTimeStep(void* sim, float interval);
API void SimDoStep(void* sim);

API void SimSetAgentDefaults(
  void* sim,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst,
  float radius, float maxSpeed, float vel_x, float vel_y
);

API size_t SimAddAgent(void* sim, float x, float y);
API size_t SimAddAgentEx(
  void* sim,
  float x, float y, float radius, float maxSpeed, float vel_x, float vel_y,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst
);

API void SimAddObstacle(void* sim, float* vertices, int total);
API void SimProcessObstacles(void* sim);

API void SimSetAgentRadius(void* sim, size_t agent_no, float radius);
API void SimSetAgentPosition(void* sim, size_t agent_no, float x, float y);
API void SimSetAgentNeighborDist(void* sim, size_t agent_no, float dist);
API void SimSetAgentMaxNeighbors(void* sim, size_t agent_no, size_t max_nbs);
API void SimSetAgentMaxSpeed(void* sim, size_t agent_no, float max_speed);
API void SimSetAgentPrefVelocity(void* sim, size_t agent_no, float vx, float vy);
API void SimSetAgentVelocity(void* sim, size_t agent_no, float vx, float vy);
API void SimSetAgentPosAndVel(void* sim, size_t agent_no, float x, float y, float vx, float vy, float pvx, float pvy);

API size_t SimGetNumAgents(void* sim);
API float SimGetTimeStep(void* sim);
API float SimGetTime(void* sim);
API void SimGetAgentPosition(void* sim, size_t agent_no, float pos[2]);
API void SimGetAgentPerfVelocity(void* sim, size_t agent_no, float vel[2]);
API void SimGetAgentVelocity(void* sim, size_t agent_no, float vel[2]);
API void SimGetAgentPosAndVel(void* sim, size_t agent_no, float pos[2], float vel[2]);
}