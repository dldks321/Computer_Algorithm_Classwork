rf = open('jug.inp','r')

s1, s2, s3 = list(map(int,rf.readline().split()))

N_list = []

for x in range(10) :
	N_list.append(int(rf.readline()))

max_N = max(N_list)

rf.close()

ans = []

for x in range(max_N+1) :
	ans.append(['S','X','X','X'])

for x in range(s1) :
	ans[x][0] = 'F'

for x in range(s1,s2) :
	if('F' in [ans[x-s1][0], ans[x-s1][2], ans[x-s1][3]]) :
		ans[x][1] = 'S'
	else :
		ans[x][1] = 'F'
		
for x in range(s2,s3) :
	if('F' in [ans[x-s2][0], ans[x-s2][1], ans[x-s2][3]]) :
		ans[x][2] = 'S'
	else :
		ans[x][2] = 'F'
	if('F' in [ans[x-s1][0], ans[x-s1][2], ans[x-s1][3]]) :
		ans[x][1] = 'S'
	else :
		ans[x][1] = 'F'

for x in range(s3,max_N+1) :
	if('F' in [ans[x-s3][0], ans[x-s3][1], ans[x-s3][2]]) :
		ans[x][3] = 'S'
	else :
		ans[x][3] = 'F'
	if('F' in [ans[x-s2][0], ans[x-s2][1], ans[x-s2][3]]) :
		ans[x][2] = 'S'
	else :
		ans[x][2] = 'F'
	if('F' in [ans[x-s1][0], ans[x-s1][2], ans[x-s1][3]]) :
		ans[x][1] = 'S'
	else :
		ans[x][1] = 'F'

f = open('jug.out','w')

for x in range(10) :
        if('F' in ans[N_list[x]]) :
                f.write('F'+'\n')
        else :
                f.write('S'+'\n')

f.close()
