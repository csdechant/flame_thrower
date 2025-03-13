#include "FlameThrowerApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
FlameThrowerApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

FlameThrowerApp::FlameThrowerApp(InputParameters parameters) : MooseApp(parameters)
{
  FlameThrowerApp::registerAll(_factory, _action_factory, _syntax);
}

FlameThrowerApp::~FlameThrowerApp() {}

void
FlameThrowerApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAllObjects<FlameThrowerApp>(f, af, syntax);
  Registry::registerObjectsTo(f, {"FlameThrowerApp"});
  Registry::registerActionsTo(af, {"FlameThrowerApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
FlameThrowerApp::registerApps()
{
  registerApp(FlameThrowerApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
FlameThrowerApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  FlameThrowerApp::registerAll(f, af, s);
}
extern "C" void
FlameThrowerApp__registerApps()
{
  FlameThrowerApp::registerApps();
}
