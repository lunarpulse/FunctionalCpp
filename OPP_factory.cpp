/*
 * =============================================================================
 *
 *       Filename:  OPP_factory.cpp
 *
 *    Description: factory function 
 *
 *        Version:  1.0
 *        Created:  29/11/18 15:36:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

class VehiclePart { };
class Wheel:public VehiclePart { };
class CarWheel:public Wheel { };
class TrainWheel:public Wheel { };

class Motor:public VehiclePart { };
class CarMotor:public Motor { };
class TrainMotor:public Motor { };

class VehiclePartFactory
{
public:
  virtual std::unique_ptr < VehiclePart > CreateMotor () const = 0;
  virtual std::unique_ptr < VehiclePart > CreateWheel () const = 0;
};

class CarPartFactory:public VehiclePartFactory
{
public:
  std::unique_ptr < VehiclePart > CreateMotor () const override
  {
    return std::make_unique < CarMotor > ();
  }
  std::unique_ptr < VehiclePart > CreateWheel () const override
  {
    return std::make_unique < CarWheel > ();
  }
};

class TrainPartFactory:public VehiclePartFactory
{
public:
  std::unique_ptr < VehiclePart > CreateMotor () const override
  {
    return std::make_unique < TrainMotor > ();
  }
  std::unique_ptr < VehiclePart > CreateWheel () const override
  {
    return std::make_unique < TrainWheel > ();
  }
};

void UseFactory (const VehiclePartFactory & factory)
{
  const auto motor = factory.CreateMotor ();
  const auto leftWheel = factory.CreateWheel ();
  // ...
}

int main ()
{
  UseFactory (CarPartFactory ());
  UseFactory (TrainPartFactory ());
}
