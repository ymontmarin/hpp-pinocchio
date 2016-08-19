//
// Copyright (c) 2016 CNRS
// Author: NMansard from Florent Lamiraux
//
//
// This file is part of hpp-pinocchio
// hpp-pinocchio is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-pinocchio is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-pinocchio  If not, see
// <http://www.gnu.org/licenses/>.

# include <hpp/pinocchio/device-object-vector.hh>

# include <pinocchio/multibody/geometry.hpp>

# include <hpp/pinocchio/joint.hh>
# include <hpp/pinocchio/device.hh>
# include <hpp/pinocchio/collision-object.hh>

namespace hpp {
  namespace pinocchio {

    CollisionObjectPtr_t DeviceObjectVector::at(const size_type i)
    { 
      selfAssert();
      return CollisionObjectPtr_t (new CollisionObject(devicePtr,i)); 
    }

    CollisionObjectConstPtr_t DeviceObjectVector::at(const size_type i) const
    { 
      selfAssert();
      return CollisionObjectConstPtr_t (new CollisionObject(devicePtr,i)); 
    }

    size_type DeviceObjectVector::size() const
    { return devicePtr->geomModel().ngeoms; }
    
    void DeviceObjectVector::selfAssert(size_type i) const
    {
      assert(devicePtr);
      assert(i<size());
    }

    /* --- ObjectVector --------------------------------------------------------- */
    CollisionObjectPtr_t ObjectVector::at(const size_type i)
    {
      return CollisionObjectPtr_t(new CollisionObject(devicePtr,jointIndex,i,inOutType));
    }

    CollisionObjectConstPtr_t ObjectVector::at(const size_type i) const
    {
      return CollisionObjectConstPtr_t(new CollisionObject(devicePtr,jointIndex,i,inOutType));
    }

    size_type ObjectVector::size() const
    {
      if( inOutType==INNER )
        return size_type(devicePtr->geomModel().innerObjects[jointIndex].size());
      else
        return size_type(devicePtr->geomModel().outerObjects[jointIndex].size());
    }
    
    void ObjectVector::selfAssert(size_type i) const
    {
      assert(devicePtr);
      assert(int(jointIndex)<devicePtr->model().njoint);
      assert(i<size());
    }

    /* --- JointVector --------------------------------------------------------- */
    
    /* Access to pinocchio index + 1 because pinocchio first joint is the universe. */
    JointPtr_t JointVector::at(const size_type i) 
    { selfAssert(i); return JointPtr_t(new Joint(devicePtr,i+1)); }
    
    /* Access to pinocchio index + 1 because pinocchio first joint is the universe. */
    JointConstPtr_t JointVector::at(const size_type i) const 
    { selfAssert(i); return JointConstPtr_t(new Joint(devicePtr,i+1)); }

    size_type JointVector::size() const 
    { return devicePtr->model().njoint - 1; }

    size_type JointVector::iend() const 
    { return size(); }

    void JointVector::selfAssert(size_type i) const
    {
      assert(devicePtr);
      assert(i>=ibegin());
      assert(i<iend());
    }
  } // namespace pinocchio
} // namespace hpp
