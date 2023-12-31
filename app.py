def main():
    # timestamp

    timestamp = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
    # informação de hardware
    r = os.popen('wmic cpu get name')
    cpu = r.read().strip()
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

if __name__ == '__main__':
    import os 
    import psutil
    import datetime
    main()