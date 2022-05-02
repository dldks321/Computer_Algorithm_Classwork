def test_pali(stri) :
	res = 1
	flag = 0
	front = 0
	back = 1
	for x in range(len(stri)//2) :
		if(stri[x+front] != stri[-(back+x)]) :
			if(stri[x+1] == stri[-(x+1)] and flag == 0) :
				front = 1
				flag = 1
				res = 2
			elif(stri[x] == stri[-(x+2)] and flag == 0) :
				back = 2
				flag = 1
				res = 2
			else :
				res = 3
				break
	return res

rf = open('palin.inp','r')
N = int(rf.readline())
ans = []

for x in range(N) :
	stri = rf.readline()
	ans.append(test_pali(stri.rstrip('\n')))
rf.close()

ans = list(map(str, ans))

f = open('palin.out','w')
for x in ans :
        f.write(x+'\n')
f.close()
