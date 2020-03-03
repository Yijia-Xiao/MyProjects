# Report for Hw 8
> 肖易佳 计算机83

## T1
- I think this is the most important and difficult part in this homework, because it is the basis of gradient descend
- The trick used in the derivation of $\frac{\partial f}{\partial parameter}$ is:
  - Use the derivative of the frontier layers to represent that of the latter layers (backforward process)
  - Use matrix and vector, can make the form of derivative simpler

## T2
- The great design is that the TA has seperated the codes into 2 parts, the fisrt is derivation, the second is updating, training, and testing
  - The check point of gradient can help us to check which part is wrong, and help us to understand the training process-->
    - Forward, and calculate the $\Delta$
    - Backward propogation, update the parameters
    - When the stopping criteria is met, we can stop training
    - Calculate the test accuray, to evaluate the generalization ability of the model
- Be careful when multiply matrix, make sure the size match

## PS
- The explanation of the MLP is written as comment in the py file
- The learning rate and training epoch may not be omtimal, but due to the restricted calculating resources: the current hyper-parameters can reach over 90% accuracy, we can just make do with these