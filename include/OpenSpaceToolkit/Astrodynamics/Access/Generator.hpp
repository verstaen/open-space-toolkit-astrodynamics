////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Astrodynamics
/// @file           OpenSpaceToolkit/Astrodynamics/Access/Generator.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Astrodynamics_Access_Generator__
#define __OpenSpaceToolkit_Astrodynamics_Access_Generator__

#include <OpenSpaceToolkit/Astrodynamics/Access.hpp>
#include <OpenSpaceToolkit/Astrodynamics/Trajectory.hpp>

#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/AER.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace astro
{
namespace access
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Real ;
using ostk::core::ctnr::Array ;

using ostk::math::obj::Interval ;

using ostk::physics::units::Length ;
using ostk::physics::units::Angle ;
using ostk::physics::time::Instant ;
using ostk::physics::coord::spherical::AER ;
using ostk::physics::Environment ;

using ostk::astro::Trajectory ;
using ostk::astro::Access ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Generator
{

    public:

                                Generator                                   (   const   Environment&                anEnvironment                               ) ;

                                Generator                                   (   const   Environment&                anEnvironment,
                                                                                const   std::function<bool (const AER&)>& anAerFilter,
                                                                                const   std::function<bool (const Access&)>& anAccessFilter                     =   {} ) ;

        bool                    isDefined                                   ( ) const ;

        Array<Access>           computeAccesses                             (   const   physics::time::Interval&    anInterval,
                                                                                const   Trajectory&                 aFromTrajectory,
                                                                                const   Trajectory&                 aToTrajectory                               ) const ;

        void                    setStep                                     (   const   Duration&                   aStep                                       ) ;

        void                    setTolerance                                (   const   Duration&                   aTolerance                                  ) ;

        void                    setAerFilter                                (   const   std::function<bool (const AER&)>& anAerFilter                           ) ;

        void                    setAccessFilter                             (   const   std::function<bool (const Access&)>& anAccessFilter                     ) ;

        static Generator        Undefined                                   ( ) ;

        /// @brief              Constructs an access generator with defined AER ranges
        ///
        /// @param              [in] anAzimuthRange An azimuth interval [deg]
        /// @param              [in] anElevationRange An elevation interval [deg]
        /// @param              [in] aRangeRange A range interval [m]
        /// @param              [in] anEnvironment An environment
        /// @return             An access generator

        static Generator        AerRanges                                   (   const   Interval<Real>&             anAzimuthRange,
                                                                                const   Interval<Real>&             anElevationRange,
                                                                                const   Interval<Real>&             aRangeRange,
                                                                                const   Environment&                anEnvironment                               ) ;

    private:

        Environment             environment_ ;

        Duration                step_ ;
        Duration                tolerance_ ;

        std::function<bool (const AER&)> aerFilter_ ;
        std::function<bool (const Access&)> accessFilter_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
