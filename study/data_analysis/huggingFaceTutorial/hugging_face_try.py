from transformers import AutoTokenizer
import numpy as np
import torch

# load data
data = np.loadtxt('train.csv', delimiter=",")
print(data[0])