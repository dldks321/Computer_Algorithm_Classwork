import sys
sys.setrecursionlimit(10**6)

def radix_sort(lis, l) :
    if(len(lis) <= 1) :
        return lis
    radix = [[],[],[],[],[]]
    for x in lis :
        if(l+1 > len(x)) :
            radix[0].append(x)
        else :
            radix["acgt".index(x[l])+1].append(x)
    #print(radix)
    if(lis == radix[0]) :
        return lis
    else :
        return radix_sort(radix[0],l+1) + radix_sort(radix[1],l+1) + radix_sort(radix[2],l+1) + radix_sort(radix[3],l+1) + radix_sort(radix[4],l+1)

def radix_find(lis, l, N) :
    if(len(lis) == 1) :
        return lis[0]
    radix = [[],[],[],[],[]]
    for x in lis :
        if(l+1 > len(x)) :
            radix[0].append(x)
        else :
            radix["acgt".index(x[l])+1].append(x)
    #print(radix)
    if(lis == radix[0]) :
        return lis[0]
    if(len(radix[0]) >= N) :
        return radix_find(radix[0],l+1,N)
    elif(len(radix[0])+len(radix[1]) >= N) :
        return radix_find(radix[1],l+1,N-len(radix[0]))
    elif(len(radix[0])+len(radix[1])+len(radix[2]) >= N) :
        return radix_find(radix[2],l+1,N-len(radix[0])-len(radix[1]))
    elif(len(radix[0])+len(radix[1])+len(radix[2])+len(radix[3]) >= N) :
        return radix_find(radix[3],l+1,N-len(radix[0])-len(radix[1])-len(radix[2]))
    else :
        return radix_find(radix[4],l+1,N-len(radix[0])-len(radix[1])-len(radix[2])-len(radix[3]))


rf = open('read.inp','r')
dna = []
'''
dna = rf.read().split()
'''
while(1):
    lines = rf.readlines(200000000)
    if not lines:
        break
    for line in lines:
        dna.append(line.rstrip())

rf.close()

N = len(dna)

ans = [int(N/5),int(2*N/5),int(3*N/5),int(4*N/5)]

l = 0

#dna = radix_sort(dna,l)

wf = open('read.out','w')
#wf.write(dna[ans[0]]+'\n'+dna[ans[1]]+'\n'+dna[ans[2]]+'\n'+dna[ans[3]])
wf.write(radix_find(dna,l,ans[0]+1)+'\n'+radix_find(dna,l,ans[1]+1)+'\n'+radix_find(dna,l,ans[2]+1)+'\n'+radix_find(dna,l,ans[3]+1))
wf.close()
