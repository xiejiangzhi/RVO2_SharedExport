local ffi = require 'ffi'

ffi.cdef[[
void* NewSim();
void FreeSim(void* sim);
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
void SimGetAgentPosition(void* sim, size_t agent_no, float pos[2]);
void SimGetAgentPerfVelocity(void* sim, size_t agent_no, float vel[2]);
void SimGetAgentVelocity(void* sim, size_t agent_no, float vel[2]);
void SimGetAgentPosAndVel(void* sim, size_t agent_no, float pos[2], float vel[2]);

]]


local M = {}
M.__index = M

local Lib = nil

function M.setup(path)
  Lib = ffi.load(path)
  return Lib
end

function M.new()
  assert(Lib, "Must setup before usage.")
  local sim = Lib.NewSim()
  ffi.gc(sim, Lib.FreeSim)
  return setmetatable({
    sim = sim,
  }, M)
end

function M:set_time_step(interval)
  assert(interval > 0, "Invalid interval")
  Lib.SimSetTimeStep(self.sim, interval)
end

function M:set_agent_default(neighbor_dist, max_neighbors, time_horizon, time_horizon_obst, radius, max_speed)
  Lib.SimSetAgentDefaults(
    self.sim,
    neighbor_dist, max_neighbors, time_horizon, time_horizon_obst,
    radius or 10, max_speed or 120, 0, 0
  );
end

function M:add_agent(x, y)
  return Lib.SimAddAgent(self.sim, x, y)
end

function M:set_agent_pref_vel(id, pvx, pvy)
  Lib.SimSetAgentPrefVelocity(self.sim, id, pvx, pvy)
end

function M:set_agent_pos_and_vel(id, x, y, vx, vy, pvx, pvy)
  Lib.SimSetAgentPosAndVel(self.sim, id, x, y, vx, vy, pvx, pvy)
end

function M:do_step()
  Lib.SimDoStep(self.sim)
end

function M:get_agent_pos_and_vel(id)
  local fv4 = ffi.new('float[4]')
  Lib.SimGetAgentPosAndVel(self.sim, id, fv4, fv4 + 2)
  return fv4[0], fv4[1], fv4[2], fv4[3]
end


if not (...) then
  M.setup('../build/SharedExport/Release/librvo2.dll')
  local sim = M.new()
  sim:set_agent_default(15, 10, 5, 5, 6, 120)
  sim:set_time_step(0.1)

  local a1 = sim:add_agent(0, 0)
  local a2 = sim:add_agent(0, 0)
  sim:set_agent_pos_and_vel(a1, -10, 0, 0, 0, 10, 0)
  sim:set_agent_pos_and_vel(a2, 10, 0, 0, 0, 10, 0)

  sim:do_step()
  print(sim:get_agent_pos_and_vel(a1))
  print(sim:get_agent_pos_and_vel(a2))
end