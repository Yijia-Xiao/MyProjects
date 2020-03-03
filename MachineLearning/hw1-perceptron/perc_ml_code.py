import pandas as pd
# import numpy as np
import random

# def shuffle(X, Y, seed=None):
# 	if seed is not None:
# 		random.seed(seed)
# 	Z = list(zip(X, Y))
# 	random.shuffle(Z)
# 	X[:], Y[:] = zip(*Z)

def mean(L):
	return sum(L) / len(L)

def import_data(xpath="", ypath=""):
	xtable = pd.read_csv(xpath)
	xtable = xtable.T
	xtable = xtable[1:]
	X = xtable.values.tolist()
	# print(X)
	ytable = pd.read_csv(ypath)
	Y = (ytable[ytable.columns[1]] == "fibroblast").tolist()
	Y = [-1.0 if y else 1.0 for y in Y]
	# print(Y)
	# print(len(X), len(Y))
	return (X, Y)

NUM_EPOCH = 10000
learning_rate = 1e-5
# when rate is 1e-5, Final Test On Test_Set Acc = 0.840000, Loss = 0.061063
# when rate is 1e-4, Final Test On Test_Set Acc = 0.900000, Loss = 0.000499
# when rate is 1e-3, Final Test On Test_Set Acc = 0.910000, Loss = 0.000686
n = 10



# Here we leave about 1/10 of training data to validate the model
data = import_data("train_10gene.csv", "train_label.csv")
data_train = (data[0][:270], data[1][:270])
data_valid = (data[0][270:], data[1][270:])
data_test = import_data("test_10gene.csv", "test_label.csv")



# Here, due to the limited size of training data in 'train_10gene_sub.csv',
# the validation will not work(according to my test, 
# so if you want to run on the smaller training set, please commet the validation part, 
# or the program cannot run - divided by 0)

# experriment 2
# data = import_data("train_10gene_sub.csv", "train_10gene_label_sub.csv")
# data_train = (data[0][:30], data[1][:30])
# data_valid = (data[0][30:], data[1][30:])

# but the final_test on test_set will work
# eg. my training result 
# When we select 35 instances, Final Test On Test_Set Acc = 0.890000, Loss = 0.050029
# When we select 30 instances, Final Test On Test_Set Acc = 0.840000, Loss = 0.061063


w = [random.random() - 0.5 for _ in range(n)]
b = random.random() - 0.5

def output(w, x):
	# return random.random()
	return sum([w[i] * x[i] for i in range(n)]) + b

def grad(x, o, y):
	return ([-x[i] * y for i in range(n)], -y) if o * y <= 0 else ([0] * n, 0)

def loss(o, y):
	return -o * y if o * y < 0 else 0

def acc(x, y):
	return output(w, x) * y > 0

def train():
	global w, b
	for epoch in range(0, NUM_EPOCH):
		# shuffle(data_train[0], data_train[1])
		for x, y in zip(data_train[0], data_train[1]):
			d = grad(x, output(w, x), y)
			for i in range(n):
				w[i] -= learning_rate * d[0][i]
			b -= learning_rate * d[1]
		if epoch % 100 == 0:
			print("epoch: %d" % epoch)
			test()
	pass

def test():
	print("acc = %lf, loss = %lf" % (
		mean([acc(x, y) for x, y in zip(data_valid[0], data_valid[1])]),
		mean([loss(output(w, x), y) for x, y in zip(data_valid[0], data_valid[1])]),
		
	))

def test_final():
	print("Final Test On Test_Set Acc = %lf, Loss = %lf" % (
		mean([acc(x, y) for x, y in zip(data_test[0], data_test[1])]),
		mean([loss(output(w, x), y) for x, y in zip(data_test[0], data_test[1])]),
	))

def main():
	train()
	test_final()
	pass

if __name__ == '__main__':
	main()
