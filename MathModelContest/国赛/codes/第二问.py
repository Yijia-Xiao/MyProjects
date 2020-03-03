import matplotlib.pyplot as plt
import math
import csv

theta2h = []  #由theta查表得到h
with open("") as csvfile:  #绝对路径名已省去
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        theta2h.append(float(row[1]))

p2rho = []  #由p查表得到rho
with open("") as csvfile:  #绝对路径名已省去
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        p2rho.append(float(row[2]))

p2E = {}  #由p查表得到E
with open("") as csvfile:  #绝对路径名已省去
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        p2E[float(row[0])] = float(row[1])

t2A = {}  #由t查表得到A
with open("") as csvfile:  #绝对路径名已省去
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        t2A[float(row[0])] = float(row[1])

out_p = [0.1, 0.5, 1, 2, 3, 4, 5, 10]  #喷油嘴外界压力
V = 500*3.1416*25
min_T_ls = []
min_phase_ls = []
min_loss = 10000000

def Qn(pressure,w,n,phase):  #入油流速
    """w is the change on theta after delta t"""
    theta = w*(n+phase)
    left = int(100*(theta%6.28)+0.000001)
    leftpre = int(100*((theta-w)%6.28)+0.000001)
    right = int(10*pressure+0.000001)
    length = theta2h[left]
    rholeft0 = 0.80455*114.7583/(3.1415926*(7.239-length)*2.5*2.5+20)
    rhoright = p2rho[right]
    if rholeft0 <= rhoright:
        return 0
    else:
        deltalength = theta2h[left]-theta2h[leftpre]
        Qn_delta_t = deltalength*3.1415926*2.5*2.5
        if Qn_delta_t > 0:
            return Qn_delta_t
        else:
            return 0

def qn_delta_p(inpressure,time,outpressure,phase):  #出油流速
    time = time%100
    time -= 1
    if time*100 < phase or time*100 > phase+245:
        return 0
    delta_p = 0
    for t in range(time*100, (time+1)*100):
        if t < phase or t > phase+245:
            continue
        elif t > phase+45 and t < phase+200:
            right = int(10 * inpressure + 0.000001)
            rhoright = p2rho[right]
            q = 1.8505*math.sqrt((inpressure-outpressure)/rhoright)
            delta_delta_p = 0.01*q*p2E[int(inpressure*10+0.5)/10]/V
            inpressure -= delta_delta_p
            delta_p += delta_delta_p
        else:
            right = int(10 * inpressure + 0.000001)
            rhoright = p2rho[right]
            q = t2A[(t-phase)/100]*math.sqrt((inpressure-outpressure)/rhoright)
            delta_delta_p = 0.01 * q * p2E[int(inpressure * 10 + 0.5) / 10] / V
            inpressure -= delta_delta_p
            delta_p += delta_delta_p
    return delta_p


for outpressure in out_p:
    print(outpressure)
    min_T = 0
    min_phase = 0
    min_loss = 10000000
    for phase in range(80, 121):  #遍历初始相位差，单位1ms
        for T in range(2510, 2525):  #遍历凸轮周期，单位0.1ms
            T = T/10
            #for phase
            w = 2*3.1415926/T
            p = {0: 100}  # 压强p(t)
            E = {0: 2171.4}  # 模量E(t)
            for time in range(1, int(T*100)):
                p0 = p[time-1]
                Q = Qn(p0, w, time, phase)
                q = qn_delta_p(p0, time, outpressure, 0)
                p0 = p0+Q*E[time-1]/V-q  #下一时刻的油管压力
                p[time] = p0
                E[time] = p2E[int(p0*10+0.5)/10]
            loss = 0
            for t in p:
                loss += (p[t]-100)*(p[t]-100)
            loss = math.sqrt(loss/int(T*100))
            #print(str(count)+":done!")
            #print(loss)
            if loss < min_loss:
                min_loss = loss
                print(min_loss, T, phase)
                min_T = T
                min_phase = phase
    min_T_ls.append(min_T)
    min_phase_ls.append(min_phase)

