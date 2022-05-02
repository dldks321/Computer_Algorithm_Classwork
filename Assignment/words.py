def Boyer_Moore_Vote(words) :
	count = 0
	maj_word = ""
	for w in words :
		if(count == 0) :
			maj_word = w
		if(maj_word == w) :
			count += 1
		else :
			count -= 1
	if(count > 0) :
		return Major_test(words, maj_word)
	else :
		return "NONE"

def Major_test(words, word) :
	if(words.count(word) > len(words)//2) :
		return word
	else :
		return "NONE"

rf = open('words.inp','r')
N = int(rf.readline())

words = []

for x in range(N) :
	words.append(rf.readline().rstrip('\n'))
rf.close()

f = open('words.out','w')
f.write(Boyer_Moore_Vote(words))
f.close()
