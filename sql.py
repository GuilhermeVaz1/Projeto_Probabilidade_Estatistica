import psycopg2 as psql
import os
import pandas as pd

conn = psql.connect(
    host='localhost',
    database='algoritmos',
    user='postgres',
    password='ypghck52'
)

cur = conn.cursor()

for dir in os.listdir('./output'):
    if '2023' not in dir:
        continue
    f = open(f'./output/{dir}/hardware_info.txt', 'r')
    f.readline()
    f.readline()
    cpu = f.readline().strip('\n')
    ram = f.readline()
    f.close()
    cur.execute(f"SELECT EXISTS(SELECT 1 FROM hardware WHERE cpu='{cpu}' AND ram={ram})")
    ret = cur.fetchone()
    conn.commit()
    if ret[0]:
        cur.execute(f"SELECT id FROM hardware WHERE cpu='{cpu}' AND ram={ram}")
        hardware_id = cur.fetchone()[0]
        conn.commit()
    else:
        cur.execute(f"INSERT INTO hardware (cpu, ram) VALUES ('{cpu}', {ram})")
        conn.commit()
        cur.execute(f"SELECT id FROM hardware WHERE cpu='{cpu}' AND ram={ram}")
        hardware_id = cur.fetchone()[0]
        conn.commit()
    bubble_result = pd.read_csv(f'./output/{dir}/bubble_log.csv')
    for index, row in bubble_result.iterrows():
        cur.execute(f"SELECT EXISTS(SELECT 1 FROM bubble_results WHERE hardware_id={hardware_id} AND size={row['size']} AND time1={row[' time1']} AND time2={row[' time2']} AND time3={row[' time3']} AND time4={row[' time4']} AND time5={row[' time5']})")
        conn.commit()
        ret = cur.fetchone()[0]
        if not ret:
            cur.execute(f"INSERT INTO bubble_results (hardware_id, size, time1, time2, time3, time4, time5) VALUES ({hardware_id}, {row['size']}, {row[' time1']}, {row[' time2']}, {row[' time3']}, {row[' time4']}, {row[' time5']})")
            conn.commit()
    merge_result = pd.read_csv(f'./output/{dir}/merge_log.csv')
    for index, row in merge_result.iterrows():
        cur.execute(f"SELECT EXISTS(SELECT 1 FROM merge_results WHERE hardware_id={hardware_id} AND size={row['size']} AND time1={row[' time1']} AND time2={row[' time2']} AND time3={row[' time3']} AND time4={row[' time4']} AND time5={row[' time5']})")
        conn.commit()
        ret = cur.fetchone()[0]
        if not ret:
            cur.execute(f"INSERT INTO merge_results (hardware_id, size, time1, time2, time3, time4, time5) VALUES ({hardware_id}, {row['size']}, {row[' time1']}, {row[' time2']}, {row[' time3']}, {row[' time4']}, {row[' time5']})")
            conn.commit()
    quick_result = pd.read_csv(f'./output/{dir}/quick_log.csv')
    for index, row in quick_result.iterrows():
        cur.execute(f"SELECT EXISTS(SELECT 1 FROM quick_results WHERE hardware_id={hardware_id} AND size={row['size']} AND time1={row[' time1']} AND time2={row[' time2']} AND time3={row[' time3']} AND time4={row[' time4']} AND time5={row[' time5']})")
        conn.commit()
        ret = cur.fetchone()[0]
        if not ret:
            cur.execute(f"INSERT INTO quick_results (hardware_id, size, time1, time2, time3, time4, time5) VALUES ({hardware_id}, {row['size']}, {row[' time1']}, {row[' time2']}, {row[' time3']}, {row[' time4']}, {row[' time5']})")
            conn.commit()

