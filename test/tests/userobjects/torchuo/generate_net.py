import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset

print(torch.__version__)
torch.manual_seed(42)

# This is an example of a neural network that will determine the dislocation density
# based on strain and temperature (might not be physical, this is just an example)
class MyNet(nn.Module):
    def __init__(self):
        super(MyNet, self).__init__()

        # We have two linear layers, we can add more if needed
        self.layer1 = nn.Linear(5, 5)
        self.output_layer = nn.Linear(5, 1)

    def forward(self, x):
        x = self.layer1(x)
        x = self.output_layer(x)
        return x

# Alright, time to train a neural net
model = MyNet()

for param in model.parameters():
  print(param)

print("Saving NN.")
scripted_model = torch.jit.script(model.double())
scripted_model.save("my_net.pt")
