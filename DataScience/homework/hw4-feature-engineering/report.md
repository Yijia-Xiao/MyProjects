# Report for homework 4

`(hw4-feature-engineering)`

`肖易佳 计算机83`

## Question 01
- Good features should be characteristic and unique of the objects, so that we can use these features to tell the difference between them.

## Question 02
- Pixels are not unique, we need to consider a certain area of pixels as a possible feature.
- However, which area should we choose, and what shape should it be is tricky.

## Question 03
- In my opinion, the key is that we need to match the evaluation mathod with the learning algorithm. Considering active learning is nor supervised learning or unsupervised learning, so I think we need to consider the whole data set, and 'Maxnimum method' just fit this feature.

## Question 04
- The task is to convert the words into vectors(I think it is like the trick used in NLP)
- Use sklearn's CountVectorizer function can achieve this goal

## Question 05
- TF-IDF is a common method in search-engine, (倒排索引) 
- Use fit_transform() can achieve this goal.

## Question 06
- Word2vec is also used in NLP, its main task is to convert the words in corpus into vectors, so that we can manipulate them easily.
- Use W2VTransformer() can implement this.

## Question 07
- Time series's part, I am not sure about its application in AI.
- But the implementation is easy, seasonal_decompose is efficient.

## Question 08
- FFT problem, use package numpy is enough.

## Question 09
- Rescaling and extracting features in the rescaled image: opencv, cv2 are enough
- Notice: in the future, if i want to carry out sift, converting the original RGB image into gray image is a good idea.

## Question 10
- Similar to Q9, just rotate and extract features.
