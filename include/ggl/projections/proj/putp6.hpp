#ifndef GGL_PROJECTIONS_PUTP6_HPP
#define GGL_PROJECTIONS_PUTP6_HPP

// Generic Geometry Library - projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright Barend Gehrels (1995-2009), Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande (2008-2009)
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <ggl/projections/impl/base_static.hpp>
#include <ggl/projections/impl/base_dynamic.hpp>
#include <ggl/projections/impl/projects.hpp>
#include <ggl/projections/impl/factory_entry.hpp>

namespace ggl { namespace projection
{
    #ifndef DOXYGEN_NO_IMPL
    namespace impl { namespace putp6{
            static const double EPS = 1e-10;
            static const int NITER = 10;
            static const double CON_POLE = 1.732050807568877;

            struct par_putp6
            {
                double C_x, C_y, A, B, D;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename LatLong, typename Cartesian, typename Parameters>
            struct base_putp6_spheroid : public base_t_fi<base_putp6_spheroid<LatLong, Cartesian, Parameters>, LatLong, Cartesian, Parameters>
            {

                typedef typename base_t_fi<base_putp6_spheroid<LatLong, Cartesian, Parameters>, LatLong, Cartesian, Parameters>::LL_T LL_T;
                typedef typename base_t_fi<base_putp6_spheroid<LatLong, Cartesian, Parameters>, LatLong, Cartesian, Parameters>::XY_T XY_T;

                par_putp6 m_proj_parm;

                inline base_putp6_spheroid(const Parameters& par)
                    : base_t_fi<base_putp6_spheroid<LatLong, Cartesian, Parameters>, LatLong, Cartesian, Parameters>(*this, par) {}

                inline void fwd(LL_T& lp_lon, LL_T& lp_lat, XY_T& xy_x, XY_T& xy_y) const
                {
                    double p, r, V;
                    int i;

                    p = this->m_proj_parm.B * sin(lp_lat);
                    lp_lat *=  1.10265779;
                    for (i = NITER; i ; --i) {
                        r = sqrt(1. + lp_lat * lp_lat);
                        lp_lat -= V = ( (this->m_proj_parm.A - r) * lp_lat - log(lp_lat + r) - p ) /
                            (this->m_proj_parm.A - 2. * r);
                        if (fabs(V) < EPS)
                            break;
                    }
                    if (!i)
                        lp_lat = p < 0. ? -CON_POLE : CON_POLE;
                    xy_x = this->m_proj_parm.C_x * lp_lon * (this->m_proj_parm.D - sqrt(1. + lp_lat * lp_lat));
                    xy_y = this->m_proj_parm.C_y * lp_lat;
                }

                inline void inv(XY_T& xy_x, XY_T& xy_y, LL_T& lp_lon, LL_T& lp_lat) const
                {
                    double r;

                    lp_lat = xy_y / this->m_proj_parm.C_y;
                    r = sqrt(1. + lp_lat * lp_lat);
                    lp_lon = xy_x / (this->m_proj_parm.C_x * (this->m_proj_parm.D - r));
                    lp_lat = aasin( ( (this->m_proj_parm.A - r) * lp_lat - log(lp_lat + r) ) / this->m_proj_parm.B);
                }
            };

            template <typename Parameters>
            void setup(Parameters& par, par_putp6& proj_parm)
            {
                par.es = 0.;
                // par.inv = s_inverse;
                // par.fwd = s_forward;
            }


            // Putnins P6
            template <typename Parameters>
            void setup_putp6(Parameters& par, par_putp6& proj_parm)
            {
                proj_parm.C_x = 1.01346;
                proj_parm.C_y = 0.91910;
                proj_parm.A   = 4.;
                proj_parm.B   = 2.1471437182129378784;
                proj_parm.D   = 2.;
                setup(par, proj_parm);
            }

            // Putnins P6'
            template <typename Parameters>
            void setup_putp6p(Parameters& par, par_putp6& proj_parm)
            {
                proj_parm.C_x = 0.44329;
                proj_parm.C_y = 0.80404;
                proj_parm.A   = 6.;
                proj_parm.B   = 5.61125;
                proj_parm.D   = 3.;
                setup(par, proj_parm);
            }

        }} // namespace impl::putp6
    #endif // doxygen

    /*!
        \brief Putnins P6 projection
        \ingroup projections
        \tparam LatLong latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp6.gif
    */
    template <typename LatLong, typename Cartesian, typename Parameters = parameters>
    struct putp6_spheroid : public impl::putp6::base_putp6_spheroid<LatLong, Cartesian, Parameters>
    {
        inline putp6_spheroid(const Parameters& par) : impl::putp6::base_putp6_spheroid<LatLong, Cartesian, Parameters>(par)
        {
            impl::putp6::setup_putp6(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P6' projection
        \ingroup projections
        \tparam LatLong latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp6p.gif
    */
    template <typename LatLong, typename Cartesian, typename Parameters = parameters>
    struct putp6p_spheroid : public impl::putp6::base_putp6_spheroid<LatLong, Cartesian, Parameters>
    {
        inline putp6p_spheroid(const Parameters& par) : impl::putp6::base_putp6_spheroid<LatLong, Cartesian, Parameters>(par)
        {
            impl::putp6::setup_putp6p(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_IMPL
    namespace impl
    {

        // Factory entry(s)
        template <typename LatLong, typename Cartesian, typename Parameters>
        class putp6_entry : public impl::factory_entry<LatLong, Cartesian, Parameters>
        {
            public :
                virtual projection<LatLong, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<putp6_spheroid<LatLong, Cartesian, Parameters>, LatLong, Cartesian, Parameters>(par);
                }
        };

        template <typename LatLong, typename Cartesian, typename Parameters>
        class putp6p_entry : public impl::factory_entry<LatLong, Cartesian, Parameters>
        {
            public :
                virtual projection<LatLong, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<putp6p_spheroid<LatLong, Cartesian, Parameters>, LatLong, Cartesian, Parameters>(par);
                }
        };

        template <typename LatLong, typename Cartesian, typename Parameters>
        inline void putp6_init(impl::base_factory<LatLong, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("putp6", new putp6_entry<LatLong, Cartesian, Parameters>);
            factory.add_to_factory("putp6p", new putp6p_entry<LatLong, Cartesian, Parameters>);
        }

    } // namespace impl
    #endif // doxygen

}} // namespace ggl::projection

#endif // GGL_PROJECTIONS_PUTP6_HPP

