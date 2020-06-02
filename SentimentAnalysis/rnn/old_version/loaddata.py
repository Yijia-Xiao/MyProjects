embdir="../data/sgns.sogou.word"
def pdchinese(word):
	for letter in word:
		if not  '\u4e00' <= letter <= '\u9fff':
			return False
	return True

unknownid=0
class embedding:
	def __init__(self,dir):
		cnt=0
		l0=[0]*300
		self.itk=['unknown']
		self.kti={'unknown':0}
		self.ite=[l0]
		self.cnt=0
		with open(dir,"r",encoding='utf-8') as f:
			for id, vec in enumerate(f.readlines()):
				emb_vec=vec.split(' ')
				if id>0:
					word=emb_vec[0]
					if pdchinese(word) and word not in self.kti:
						cnt+=1
						self.itk.append(word)
						self.kti[word]=cnt
						self.ite.append(list(map(lambda x:float(x), emb_vec[1:-1])))
			f.close()
		self.cnt=cnt
	def getemb(self,word):
		if self.kti.get(word)==None:
			return 0
		else:
			return self.kti[word]

def word_emb():
	return embedding(embdir)

s=word_emb()

