#第一问（1）
import numpy as np
import matplotlib.pyplot as plt
import math
import csv

p2E = {}  #由p查表得到E
with open("") as csvfile:  #绝对路径名已省去
    csv_reader = csv.reader(csvfile)  # 使用csv.reader读取csvfile中的文件
    header = next(csv_reader)  # 读取第一行每一列的标题
    for row in csv_reader:
        p2E[float(row[0])] = float(row[1])
        #p2E.append(row)

min_loss = 10000000
min_start = 0
min_end = 0
count = 0
start_out = 130
end_out = 370
V = 500*3.1416*25
for start_in in range(1, 250):  #开始入油时间
    for end_in in range(start_in+200, 501):  #停止入油时间
        p = {0: 100}  # 压强p(t)
        E = {0: 2171.4}  # 模量E(t)
        for time in range(1, 1001):
            p0 = p[time-1]
            if time > start_in and time < end_in:  #正在进油
                Q = 0.85*3.1416*0.49*math.sqrt(2*(160-p0)/0.8713)
                p0 += Q*0.01*E[time-1]/V  #入油导致压升
            if time > start_out and time < end_out:  #正在出油
                if (time-start_out) < 20:
                    q = time-start_out
                elif (time-start_out) > 220:
                    q = end_out-time
                else:
                    q = 20
                p0 -= q*0.01*E[time-1]/V  #出油导致压降
            p[time] = p0
            E[time] = p2E[int(p0*10+0.5)/10]
        loss = 0
        for t in p:
            loss += (p[t]-100)*(p[t]-100)
        count += 1
        #print(str(count)+":done!")
        if loss < min_loss and abs(p[900]-100) < 0.01:  #满足约束条件的同时优化损失函数
            min_loss = loss
            print(min_loss)
            min_start = start_in
            min_end = end_in