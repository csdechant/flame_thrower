//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "FlameThrowerTestApp.h"
#include "FlameThrowerApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
FlameThrowerTestApp::validParams()
{
  InputParameters params = FlameThrowerApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

FlameThrowerTestApp::FlameThrowerTestApp(InputParameters parameters) : MooseApp(parameters)
{
  FlameThrowerTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

FlameThrowerTestApp::~FlameThrowerTestApp() {}

void
FlameThrowerTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  FlameThrowerApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"FlameThrowerTestApp"});
    Registry::registerActionsTo(af, {"FlameThrowerTestApp"});
  }
}

void
FlameThrowerTestApp::registerApps()
{
  registerApp(FlameThrowerApp);
  registerApp(FlameThrowerTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
FlameThrowerTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  FlameThrowerTestApp::registerAll(f, af, s);
}
extern "C" void
FlameThrowerTestApp__registerApps()
{
  FlameThrowerTestApp::registerApps();
}
