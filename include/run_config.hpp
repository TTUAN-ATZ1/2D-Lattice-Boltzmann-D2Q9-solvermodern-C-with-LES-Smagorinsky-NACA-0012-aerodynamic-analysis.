#pragma once
#include <cmath>
#include <stdexcept>
#include <vector>

struct RunConfig
{
    int nx = 720, ny = 400, surface_points = 120, steps = 30000, average_steps = 15000;
    int sample_every = 10, health_every = 100;
    double chord = 100, u_inf = 0.04, re = 100000, cs = 0.12, x_fraction = 0.25, y_fraction = 0.5;
    double real_velocity = 3.0, real_nu = 1.5e-5, real_rho = 1.225, real_pressure = 101325;
    double max_mach = 0.5, max_density_deviation = 0.2;
    double stable_abs = 0.005, stable_rel = 0.02, min_block_times = 0.8;
    double ac_min = 0, ac_max = 10;
    bool write_vtk = true;
    std::vector<double> angles{0, 1, 2, 4, 6, 8, 10, 11, 12, 13, 14, 15, 16, 18, 20, 25, 30};

    void validate() const
    {
        if (nx < 8 || ny < 8 || chord < 8 || u_inf <= 0 || u_inf >= 0.15 || re <= 0 || cs < 0 || surface_points < 8 || surface_points % 2 != 0 || average_steps > steps || sample_every < 1 || health_every < 1 || average_steps / sample_every < 20 || (steps - average_steps) % sample_every != 0 || average_steps % sample_every != 0 || x_fraction <= 0 || x_fraction >= 1 || y_fraction <= 0 || y_fraction >= 1 || max_mach <= 0 || max_density_deviation <= 0 || stable_abs <= 0 || stable_rel < 0 || min_block_times <= 0 || ac_min > ac_max || angles.empty())
            throw std::invalid_argument("Invalid grid/run settings; averaging needs >=20 samples and aligned sampling intervals");
        for (size_t i = 0; i < angles.size(); ++i)
            if (std::abs(angles[i]) >= 90 || (i > 0 && angles[i] <= angles[i - 1]))
                throw std::invalid_argument("Angles must be strictly increasing and between -90 and 90 degrees");
    }
};
