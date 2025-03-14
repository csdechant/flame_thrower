[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 1
  ny = 1
[]

[UserObjects]
  [torch_uo]
    type = TorchUserObject
    execute_on = INITIAL
    # n_samples = 10000
    # num_neurons = '1024 1024'
    # n_epochs = 1000
    # learning_rate = 0.001
    filename = my_net.pt
  []
[]

[Problem]
  solve = false
[]

[Executioner]
  type = Steady
[]
