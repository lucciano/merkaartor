// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_EXTENSIONS_GIS_GEOGRAPHIC_CORE_CS_HPP
#define GGL_EXTENSIONS_GIS_GEOGRAPHIC_CORE_CS_HPP


/*!
\defgroup cs coordinate systems
\brief Defines coordinate systems
\details Coordinate systems are essential for any point in the Generic Geometry Library. Many
algorithms such as distance or transform use coordinate systems to select the strategy to use.
*/

namespace ggl
{

namespace cs
{

/*!
    \brief EPSG Cartesian coordinate system
    \details EPSG (European Petrol Survey Group) has a standard list of projections,
        each having a code
    \see
    \ingroup cs
    \tparam Code the EPSG code
    \todo Maybe derive from boost::mpl::int_<EpsgCode>
*/
template<std::size_t Code>
struct epsg
{
    static const std::size_t epsg_code = Code;
};



/*!
    \brief Earth Centered, Earth Fixed
    \details Defines a Cartesian coordinate system x,y,z with the center of the earth as its origin,
        going through the Greenwich
    \see http://en.wikipedia.org/wiki/ECEF
    \see http://en.wikipedia.org/wiki/Geodetic_system
    \note Also known as "Geocentric", but geocentric is also an astronomic coordinate system
    \ingroup cs
*/
struct ecef
{
};


} // namespace cs

namespace traits
{

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

template<>
struct cs_tag<cs::ecef>
{
    typedef cartesian_tag type;
};

template <std::size_t C>
struct cs_tag<cs::epsg<C> >
{
    typedef cartesian_tag type;
};

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS
} // namespace traits


} // namespace ggl

#endif // GGL_EXTENSIONS_GIS_GEOGRAPHIC_CORE_CS_HPP
