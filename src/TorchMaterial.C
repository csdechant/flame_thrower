//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TorchMaterial.h"
#include "LibtorchUtils.h"

registerMooseObject("FlameThrowerApp", TorchMaterial);

InputParameters
TorchMaterial::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(
      "Declares material properties based on names and values prescribed by input parameters.");
  params.addRequiredParam<std::vector<std::string>>(
      "prop_names", "The names of the properties this material will have");
  params.addRequiredParam<std::vector<Real>>("prop_values",
                                             "The values associated with the named properties");
  params.set<MooseEnum>("constant_on") = "SUBDOMAIN";
  params.declareControllable("prop_values");
  return params;
}

TorchMaterial::TorchMaterial(const InputParameters & parameters)
  : Material(parameters),
    _prop_names(getParam<std::vector<std::string>>("prop_names")),
    _prop_values(getParam<std::vector<Real>>("prop_values"))
{
  unsigned int num_names = _prop_names.size();
  unsigned int num_values = _prop_values.size();

  if (num_names != num_values)
    mooseError(
        "Number of prop_names must match the number of prop_values for a GenericConstantMaterial!");

  _num_props = num_names;

  _properties.resize(num_names);

  for (unsigned int i = 0; i < _num_props; i++)
    _properties[i] = &declareGenericProperty<Real, false>(_prop_names[i]);

  _nn = std::make_shared<Moose::LibtorchTorchScriptNeuralNet>("my_net.pt");
}

void
TorchMaterial::initQpStatefulProperties()
{
  computeQpProperties();
}

void
TorchMaterial::computeQpProperties()
{
  std::vector<Real> input_vector({0.1, 0.2, 0.3, 0.4, 0.5});
  torch::Tensor converted_tensor;

  LibtorchUtils::vectorToTensor(input_vector, converted_tensor);

  for (unsigned int i = 0; i < _num_props; i++)
    (*_properties[i])[_qp] = _prop_values[i];
}
