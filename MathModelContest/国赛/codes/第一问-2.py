import math
import csv
p2E = {}  #由p查表得到E
with open("") as csvfile:  #绝对路径名已省去
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        p2E[float(row[0])] = float(row[1])
        #p2E.append(row)

min_loss = 100000000
graph = []
min_c = 0
min_t = 0
min_s = 0
count = 0
V = 500*3.1416*25
for C in range(1, 40):  #遍历单向阀在每一周期内的开启时间，以0.1ms为单位
    print(C)
    for T in range(7*C, 11*C):  #遍历单向阀周期，以0.1ms为单位
        for S in range(0, 1):
            p = {0: 100}  # 压强p(t)
            E = {0: 2171.4}  # 模量E(t)
            start = S
            end = S+C
            all_in = []
            while end < 100000:
                one_in = [start, end]
                all_in.append(one_in)
                start += T
                end += T
            time_in = []  #各个时刻是否在进油
            for i in range(100001):
                time_in.append(0)
            for one_in in all_in:
                start = one_in[0]
                end = one_in[1]
                for t in range(start, end):
                    time_in[t] = 1

            start = 0
            end = 24
            all_out = []
            while end < 100000:
                one_out = [start, end]
                all_out.append(one_out)
                start += 1000
                end += 1000
            time_out = []  # 各个时刻是否在进油
            for i in range(100001):
                time_out.append(0)
            for one_out in all_out:
                start = one_out[0]
                end = one_out[1]
                time_out[start+1] = 2
                time_out[end-1] = 2
                for t in range(start+2, end-1):
                    time_out[t] = 1
            judge = False
            for time in range(1, 100001):
                p0 = p[time-1]
                if p0 > 160:
                    judge = True
                    break
                if time_in[time] == 1:  #正在进油
                    Q = 0.85*3.1416*0.49*math.sqrt(2*(160-p0)/0.8713)
                    p0 += Q*0.01*E[time-1]/V
                if time_out[time] != 0:  #正在出油
                    if time_out[time]==1:
                        q = 20
                    else:
                        q = 10
                    p0 -= q*0.01*E[time-1]/V
                p[time] = p0
                E[time] = p2E[int(p0*10+0.5)/10]
            #print(p[2500])
            loss = 0
            if judge:
                continue
            for t in p:
                loss += (p[t]-100-0.0005*t)*(p[t]-100-0.0005*t)  #更改:0.0005对应10s提升，0.001对应5s提升，0.0025对应2s提升
            #print(loss)
            count += 1
            if loss < min_loss and abs(p[99999]-150) < 0.1:  #满足约束条件的同时优化损失函数
                min_loss = loss
                #print(str(count)+":done!")
                print(min_loss)
                print(C, T, S)
                min_c = C
                min_t = T
                min_s = S