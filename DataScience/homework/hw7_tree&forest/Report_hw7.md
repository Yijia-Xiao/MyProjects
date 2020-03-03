# Report for homework 7

## In this homework, we learned about the four practical machine learning models: `logistic regression`,  `decision tree`, `random forest` and `ada boost`

- The basic procedure for training a model and validating it on the test data set is similar:
  - First, we define a model using functions provided in `sklearn` package.
  - Then we'll fit the data on the training set. 
  - And last we calculate the accuracy of the model on the test set

- Four different models: we need to be careful when we define the model. 
  - As for logistic regression, we can choose different kinds of solver: in the homework, I choose model. Also we can choose not to provide arguments and use the default kinds of solver.
  - As for the decision tree classifier, we can usually choose two kinds of criteria -- gini and cross entropy. And gini vision is the default version, for it is usually used on the smaller data set. And considering the actual situation of this homework, we choose the `gini` as the criterion
  - As for the Random forest model. There are a lot of arguments that can be user-defined. I focus on 3: first, estimators; then, max_depth; last, max_leaf_nodes. Three arguments are just like hyper-parameters. We can define them when we define the model
  - As for the ada boost, hyper-parameter is n_estimators(I choose 100)
  
- Besides, we need to iteratively change the parameters to find the best possible combination of parameters for this model & dataset. We can take the binary research strategy. First we can use larger steps. And then we narrow down the possible range of parameters. Last, we find the optimal combination. And as for this homework, because of the limitation of computer computing ability, I just carried out 2 rounds of training. 

- Last, as for the Feature engineering part
  - First, I sealed data sets & models into lists. Then I literally find the best generalization ability of different models on different kinds of data sets. And at last we can get the possible results and compare, coming to a conclusion about how these different models perform, on different kinds of data sets.