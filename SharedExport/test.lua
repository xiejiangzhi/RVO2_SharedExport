local ffi = require 'ffi'


local lib = ffi.load('../build/SharedExport/Release/librvo2.dll')

ffi.cdef[[

void* NewSim();
void SimSetTimeStep(void *sim, float interval);
void SimSetAgentDefaults(
  void* sim,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst,
  float radius, float maxSpeed, float vel_x, float vel_y
);
size_t SimAddAgent(void* sim, float x, float y);
size_t SimAddAgentEx(
  void* sim,
  float x, float y, float radius, float maxSpeed, float vel_x, float vel_y,
  float neighborDist, size_t maxNeighbors, float timeHorizon, float timeHorizonObst
);

void SimAddObstacle(void* sim, float* vertices, int total);

void SimProcessObstacles(void* sim);
void SimDoStep(void* sim);

void SimSetAgentRadius(void* sim, size_t agent_no, float radius);
void SimSetAgentPosition(void* sim, size_t agent_no, float x, float y);
void SimSetAgentNeighborDist(void* sim, size_t agent_no, float dist);
void SimSetAgentMaxNeighbors(void* sim, size_t agent_no, size_t max_nbs);
void SimSetAgentMaxSpeed(void* sim, size_t agent_no, float max_speed);
void SimSetAgentPrefVelocity(void* sim, size_t agent_no, float vx, float vy);
void SimSetAgentVelocity(void* sim, size_t agent_no, float vx, float vy);

void SimSetAgentPosAndVel(void* sim, size_t agent_no, float x, float y, float vx, float vy, float pvx, float pvy);

size_t SimGetNumAgents(void* sim);
void SimGetAgentPosition(void* sim, size_t agent_no, float* x, float* y);
void SimGetAgentPerfVelocity(void* sim, size_t agent_no, float* x, float* y);
void SimGetAgentVelocity(void* sim, size_t agent_no, float* vx, float* vy);
]]

print(lib, 123)
local sim = lib.NewSim()