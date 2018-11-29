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
class AirPlaneWheel:public Wheel { };

class Motor:public VehiclePart { };
class CarMotor:public Motor { };
class TrainMotor:public Motor { };
class AirPlaneMotor:public Motor { };

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

void
UseFactory (const VehiclePartFactory & factory)
{
  const auto motor = factory.CreateMotor ();
  const auto leftWheel = factory.CreateWheel ();
  // ...
}

/********************************************************************************
 * functional programming version
 */
enum class vehicle_type
{ Car, Train, AirPlane };
enum class part_type
{ Motor, Wheel };

std::unique_ptr < VehiclePart > create_part (vehicle_type v_t, part_type p_t)
{
  using namespace std;
  switch (v_t)
    {
    case vehicle_type::Train:
      switch (p_t)
	{
	case part_type::Motor:
	  return std::make_unique < TrainMotor > ();
	  break;
	case part_type::Wheel:
	  return std::make_unique < TrainWheel > ();
	  break;
	}
    case vehicle_type::AirPlane:
      switch (p_t)
	{
	case part_type::Motor:
	  return std::make_unique < AirPlaneMotor > ();
	  break;
	case part_type::Wheel:
	  return std::make_unique < AirPlaneWheel > ();
	  break;
	}
    case vehicle_type::Car:
      switch (p_t)
	{
	case part_type::Motor:
	  return std::make_unique < CarMotor > ();
	  break;
	case part_type::Wheel:
	  return std::make_unique < CarWheel > ();
	  break;
	}
    }
}

const auto carPartFactory =
  fplus::bind_1st_of_2 (create_part, vehicle_type::Car);
const auto trainPartFactory =
  fplus::bind_1st_of_2 (create_part, vehicle_type::Train);
const auto airPlanePartFactory =
  fplus::bind_1st_of_2 (create_part, vehicle_type::AirPlane);

typedef
  std::function < std::unique_ptr < VehiclePart > (part_type) > Factory;

void UseFunctionalFactory (const Factory & factory)
{
  const auto
    motor = factory (part_type::Motor);
  const auto
    leftWheel = factory (part_type::Wheel);
}

int
main ()
{
  using namespace
    fplus;

  UseFactory (CarPartFactory ());
  UseFactory (TrainPartFactory ());

  UseFunctionalFactory (carPartFactory);
  UseFunctionalFactory (trainPartFactory);
  UseFunctionalFactory (airPlanePartFactory);
}
