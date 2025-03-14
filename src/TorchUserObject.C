//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// torch includes
#include <torch/torch.h>

// MOOSE includes
#include "TorchUserObject.h"
#include "LibtorchArtificialNeuralNet.h"
#include "LibtorchTorchScriptNeuralNet.h"

registerMooseObject("FlameThrowerApp", TorchUserObject);

InputParameters
TorchUserObject::validParams()
{
  InputParameters params = GeneralUserObject::validParams();
  // params.addParam<unsigned int>("n_samples", 1000, "Number of samples.");
  // params.addParam<std::vector<unsigned int>>(
  //     "num_neurons", {1024, 1024}, "Number of neurons on the hidden layer.");
  // params.addParam<Real>("learning_rate", 0.001, "The learning rate.");
  // params.addParam<unsigned int>("n_epochs", 1000, "Number of epochs.");
  params.addParam<std::string>("filename", "mynet.pt", "The filename which contains the NN.");
  return params;
}

TorchUserObject::TorchUserObject(const InputParameters & parameters) : GeneralUserObject(parameters)
{
  torch::manual_seed(42);
}

void
TorchUserObject::execute()
{
  // const auto options =
  //     torch::TensorOptions().dtype(torch::kFloat32).device(_app.getLibtorchDevice());
  // const auto n_samples = getParam<unsigned int>("n_samples");

  // torch::Tensor input_tensor = torch::randn({n_samples, 5}, options);
  // torch::Tensor output_tensor = torch::randn({n_samples, 1}, options);

  // const auto num_neurons = getParam<std::vector<unsigned int>>("num_neurons");

  // auto network = Moose::LibtorchArtificialNeuralNet(
  //     "myname", 5, 1, num_neurons, {"relu", "relu"}, _app.getLibtorchDevice(), torch::kFloat32);

  // for (auto param : network.parameters())
  //   _console << param << std::endl;

  // const auto learning_rate = getParam<Real>("learning_rate");
  // const auto n_epocs = getParam<unsigned int>("n_epochs");

  // torch::optim::Adam optimizer(network.parameters(), learning_rate);

  // for (size_t epoch = 1; epoch <= n_epocs; ++epoch)
  // {
  //   // Reset gradients.
  //   optimizer.zero_grad();
  //   // Execute the model on the input data.
  //   torch::Tensor prediction = network.forward(input_tensor);
  //   // Compute a loss value to judge the prediction of our model.
  //   torch::Tensor loss = torch::mse_loss(prediction, output_tensor);
  //   // Compute gradients of the loss w.r.t. the parameters of our model.
  //   loss.backward();
  //   // Update the parameters based on the calculated gradients.
  //   optimizer.step();
  //   // Output the loss and checkpoint every 100 batches.
  //   std::cout << "Epoch: " << epoch << " | Loss: " << loss.item<double>() << std::endl;
  // }

  const auto filename = getParam<std::string>("filename");

  auto torch_script_nn = Moose::LibtorchTorchScriptNeuralNet(filename);

  for (auto param : torch_script_nn.parameters())
    _console << param << std::endl;
}
