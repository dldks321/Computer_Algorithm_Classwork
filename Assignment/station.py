import math
import sys
sys.setrecursionlimit(10 ** 6)

def line_distance(d1,d2) :
    return (((d2[0] - d1[0])**2 + (d2[1] - d1[1])**2 + (d2[2] - d1[2])**2) ** 0.5)

def mid_point(d1,d2) :
    return [(d1[0]+d2[0])/2, (d1[1]+d2[1])/2, (d1[2]+d2[2])/2]

def ot_point(d1,d2) :
    return [(9*d1[0]+1*d2[0])/10, (9*d1[1]+1*d2[1])/10, (9*d1[2]+1*d2[2])/10]

def get_distance(p1,p2,p3) :
    d1 = line_distance(p1,p2)
    d2 = line_distance(p1,p3)
    d3 = line_distance(p1,mid_point(p2,p3))
    if(d1 == 0 or d2 == 0 or d3 == 0) :
        return 0
    if(line_distance(p2,p3) < 0.0001) :
        return min(d1,d2,d3)
    if(min(d1,d2,d3) == d2) :
        return get_distance(p1,mid_point(p2,p3),p3)
    elif(min(d1,d2,d3) == d3) :
        return get_distance(p1,mid_point(p2,mid_point(p2,p3)),mid_point(mid_point(p2,p3),p3))
    else :
        return get_distance(p1,p2,mid_point(p2,p3))

rf = open('station.inp','r')

A = list(map(int,rf.readline().split()))
B = list(map(int,rf.readline().split()))
C = list(map(int,rf.readline().split()))
D = list(map(int,rf.readline().split()))

rf.close()

f = open('station.out','w')

pa = A
pb = B
pc = mid_point(A,B)

while(True) :
    da = get_distance(pa,C,D)
    db = get_distance(pb,C,D)
    dmid = get_distance(pc,C,D)
    print(da,db,dmid)
    if(da == 0 or db == 0 or dmid == 0) :
        f.write('0')
        break
    if(line_distance(pa,pb) < 0.0001) :
        ans = min(da,db,dmid)
        if(abs(ans-round(ans) < 0.0001)) :
            f.write(str(round(ans)))
        else :
            f.write(str(math.ceil(ans)))
        break
    if(min(da,db,dmid) == db) :
        pa = ot_point(pa,pb)
        pc = mid_point(pa,pb)
    elif(min(da,db,dmid) == da) :
        pb = ot_point(pb,pa)
        pc = mid_point(pa,pb)
    else :
        pa = ot_point(pa,pc)
        pb = ot_point(pb,pc)
    
f.close()
