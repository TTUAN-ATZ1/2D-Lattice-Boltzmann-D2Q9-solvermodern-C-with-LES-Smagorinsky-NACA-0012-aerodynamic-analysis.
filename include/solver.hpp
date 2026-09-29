#pragma once
#include <vector>
#include "D2Q9.hpp"
#include "Grid.hpp"
#include "geometry_naca.hpp"
#include "les_smagorinsky.hpp"
#include "momentum_exchange.hpp"
#include "collision.hpp"

namespace lbm
{
    struct FlowHealth {
        double mass=0, rho_min=0, rho_max=0, max_mach=0;
        double inlet_flux=0, outlet_flux=0, min_population=0;
    };

    class LBMSolver
    {
    public:
        int nx, ny;
        double u_inf;
        double chord_lb;
        double x_te_lab;

        Grid2D grid;
        LESSmagorinsky les;

        std::vector<NodeType> node_type;
        std::vector<double> wall_dist;
        std::vector<double> sgs_coeff;
        std::vector<BoundaryLink> ibb_links;

        AeroForce last_mea_force;

        LBMSolver(int nx_, int ny_, double u_inf_, double Re, double chord_lb, double Cs = 0.0);
        void refresh_macroscopic();
        FlowHealth health() const;

        void set_geometry(const NACAGeometry &geom);
        void step(const MomentumExchange *mea = nullptr);
    };

} // namespace lbm
