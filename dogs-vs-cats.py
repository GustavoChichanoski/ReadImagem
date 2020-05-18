import os
import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt 
import tensorflow as tf 
from scipy.misc import imresize
from sklearn.model_selection import train_test_split 
import cv2
from nets import vgg
from preprocessing import vgg_preprocessing
from mlxtend.preprocessing import shuffle_arrays_unison 
sys.path.append("/home/santanu/models/slim")

%matplotlib inline

batch_size = 32
width = 224
height = 224