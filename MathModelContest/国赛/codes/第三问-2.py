import math
import csv

theta2h = []
with open("cam.csv") as csvfile:
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        theta2h.append(float(row[1]))

p2rho = []
with open("p_E_rho_afterinterp.csv") as csvfile:
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        p2rho.append(float(row[2]))

p2E = {}
with open("p_E_rho_afterinterp.csv") as csvfile:
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        p2E[float(row[0])] = float(row[1])

t2A = {}
with open("sprayer_cAsqrt2.csv") as csvfile:
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        t2A[float(row[0])] = float(row[1])



out_p = [1]
V = 500*3.1416*25
min_T_ls = []
min_phase0_ls = []
min_phase_ls = []
min_phaseout_ls = []#减压阀
min_opentime_ls = []#减压阀
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

def qn(inpressure,time,outpressure,phase):  #出油流速
    time = (time-phase)%10000
    if time > 245:
        return 0
    elif time > 45 and time < 200:
        right = int(10 * inpressure + 0.000001)
        rhoright = p2rho[right]
        return 1.8505*math.sqrt((inpressure-outpressure)/rhoright)
    else:
        right = int(10 * inpressure + 0.000001)
        rhoright = p2rho[right]
        return t2A[time/100]*math.sqrt((inpressure-outpressure)/rhoright)

def qn3(inpressure,time, phase, T0):  #出油流速
    time = time%10000
    if time > T0 + phase or time < phase:
        return 0
    else:
        right = int(10 * inpressure + 0.000001)
        rhoright = p2rho[right]
        return 1.8505 * math.sqrt((inpressure-0.5)/rhoright)

for outpressure in out_p:
        min_T = 0
        min_phase = 0
        min_phase0 = 0
        min_phaseout=0
        min_opentime=0
        print(outpressure)
        min_loss = 10000000
        for phase0 in range(6174,6177):
            print('phase0:',phase0)
            for phase in range(1715,1718):
                print('phase:',phase)
                for phaseout in range(2935,2939):
                    for opentime in range(64,68):
                        for T in range(10000,10001):
                            T = T*1#以0.01ms为单位
                            w = 2*3.1415926/T
                            p = {0: 100}  # 压强p(t)
                            E = {0: 2171.4}  # 模量E(t)
                            try:
                                for time in range(1, int(T*10)):
                                    p0 = p[time-1]
                                    Q = Qn(p0, w, time, phase0)
                                    q = qn(p0, time, outpressure, 0)
                                    q2= qn(p0, time, outpressure, phase)
                                    q3= qn3(p0,time,phaseout,opentime)
                                    p0 = p0+Q*E[time-1]/V-q*0.01*E[time-1]/V-q2*0.01*E[time-1]/V-q3*0.01*E[time-1]/V  #原压强加上进油增加压强减去两嘴和减压阀压强
                                    p[time] = p0
                                    E[time] = p2E[int(p0*10+0.5)/10]
                                loss = 0
                                for t in p:
                                    loss += (p[t]-100)*(p[t]-100)
                                loss = math.sqrt(loss/int(T*10))
                                if loss < min_loss:
                                    min_loss = loss
                                    print(min_loss, T, phase0,phase,phaseout,opentime)
                                    min_T = T
                                    min_phase = phase
                                    min_phase0 = phase0
                                    min_phaseout = phaseout
                                    min_opentime=opentime
                            except:
                                pass
        min_phase0_ls.append(min_phase0)
        min_T_ls.append(min_T)
        min_phase_ls.append(min_phase)
        min_phaseout_ls.append(min_phaseout)
        min_opentime_ls.append(min_opentime)