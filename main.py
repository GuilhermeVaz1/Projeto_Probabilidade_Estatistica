import os
import cpuinfo
import psutil
import pandas as pd

# informação de hardware
cpu = cpuinfo.get_cpu_info()['brand_raw']
mem_gb = psutil.virtual_memory().total / pow(2,30)

# gerando logs de tempos de execução...
os.system("log.exe")

quick_sortDf = pd.read_csv("quick_log.csv", sep=",")
print(quick_sortDf)