import csv
from datetime import datetime
from locale import currency
from multiprocessing.sharedctypes import Value

from matplotlib import pyplot as plt

# 从文件中获取最高气温和日期和最低气温
filename = 'death_valley_2014.csv'
with open(filename) as f:
    reader = csv.reader(f)
    header_row = next(reader)
    
    for index, column_header in enumerate(header_row):
        print(index, column_header)
    
    dates, highs, lows = [], [], []
    for row in reader:
        # current_date = datetime.strptime(row[0], "%Y-%m-%d")
        # dates.append(current_date)
        # high = int(row[1])
        # highs.append(high)
        
        # low = int(row[3])
        # lows.append(low)
        try:
            currenct_date = datetime.strptime(row[0], "%Y-%m-%d")
            high = int(row[1])
            low = int(row[3])
        except ValueError:
            print(currenct_date, 'missing date')
        else:
            dates.append(currenct_date)
            highs.append(high)
            lows.append(low)
        
# 根据数据绘制图形
fig = plt.figure(dpi=128, figsize=(10, 6))
plt.plot(dates, highs, c='red', alpha=0.5)
plt.plot(dates, lows, c='blue', alpha=0.5)
plt.fill_between(dates, highs, lows, facecolor='blue', alpha=0.1)

# 设置图形格式
plt.title("Daily high and low temperatures - 2014", fontsize=24)
plt.xlabel(' ', fontsize=16)
fig.autofmt_xdate()
plt.ylabel('Temperature(F)', fontsize=16)
# Question:这里的witch参数是用来做什么的？
plt.tick_params(axis='both', which='major', labelsize=16)

plt.show()