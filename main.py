import os
import cpuinfo
import psutil
import datetime
import pandas as pd
from IPython.display import display

# timestamp

timestamp = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")

# informação de hardware
cpu = cpuinfo.get_cpu_info()['brand_raw']
mem_gb = psutil.virtual_memory().total / pow(2,30)

# folder name
os.mkdir(timestamp)
arquivo_txt = open(f'{timestamp}/hardware_info.txt', 'w')

arquivo_txt.write(f'{cpu}\n{round(mem_gb,0)}')


# gerando logs de tempos de execução...
os.system("log.exe")

os.rename('quick_log.csv', f'{timestamp}/quick_log.csv')
os.rename('merge_log.csv', f'{timestamp}/merge_log.csv')
os.rename('bubble_log.csv', f'{timestamp}/bubble_log.csv')