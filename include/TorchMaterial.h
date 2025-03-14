//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "LibtorchTorchScriptNeuralNet.h"
#include "Material.h"

class TorchMaterial : public Material
{
public:
  static InputParameters validParams();

  TorchMaterial(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  const std::vector<std::string> & _prop_names;
  const std::vector<Real> & _prop_values;

  unsigned int _num_props;

  std::shared_ptr<Moose::LibtorchTorchScriptNeuralNet> _nn;

  std::vector<GenericMaterialProperty<Real, false> *> _properties;
};
