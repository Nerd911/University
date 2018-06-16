from  sklearn.neural_network  import MLPClassifier
import  random , pickle
import numpy as np
from sklearn.externals import joblib

nn = MLPClassifier(hidden_layer_sizes = (60 ,60 ,10))
data = np.genfromtxt("output.txt", delimiter=',')
X = data[:,:-1]
y = data[:,-1]
nn.fit(X, y)
joblib.dump(nn, 'clf.pkl')
