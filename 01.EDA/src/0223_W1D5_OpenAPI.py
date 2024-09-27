
import os
import sys
import json
import datetime
import urllib.request
import pandas as pd

result_mol = []

def gen_search_url(api_node, search_text, start_num, disp_num):
    base = "https://openapi.naver.com/v1/search"
    node = "/" + api_node + ".json"
    param_query = "?query=" + urllib.parse.quote(search_text)
    param_start = "&start=" +str(start_num)
    param_disp = "&display=" + str(disp_num)
    return base+ node+param_query+param_start+param_disp

def get_result_onpage(url):
    request = urllib.request.Request(url)
    request.add_header("X-Naver-Client-Id",client_id)
    request.add_header("X-Naver-Client-Secret",client_secret)
    
    response = urllib.request.urlopen(request)
    print("[%s] Url Request Success" % datetime.datetime.now())

    return json.loads(response.read().decode('utf-8'))

def get_fields(json_data):
    title = [delete_tag(each['title']) for each in json_data['items']]
    link = [each['link'] for each in json_data['items']]
    lprice = [each['lprice'] for each in json_data['items']]
    hprice = [each['hprice'] for each in json_data['items']]
    mall_name = [each['mallName'] for each in json_data['items']]
        
    result_pd = pd.DataFrame({'title':title, 'lprice':lprice, 'hprice':hprice,'link':link, 'mall':mall_name},
                             columns=['title', 'lprice', 'hprice', 'link', 'mall'])
    return result_pd

def delete_tag(input_str):
    input_str = input_str.replace("<b>", "")
    input_str = input_str.replace("</b>", "")

    return input_str


client_id = "id"
client_secret = "pw"

for n in range(1,1000,100):
    url = gen_search_url('shop', '"풀"', n, 100)
    json_reuslt = get_result_onpage(url)
    pd_result = get_fields(json_reuslt)
    result_mol.append(pd_result)
result_mol=pd.concat(result_mol)

result_mol['lprice'] = result_mol['lprice'].astype('float')
result_mol['hprice'] = pd.to_numeric(result_mol['hprice'], errors='coerce')

writer = pd.ExcelWriter(
    "/home/han/Han_ws/eda/data/grass_in_naver_shop.xlsx", 
    engine='xlsxwriter'
    )
result_mol.to_excel(writer, sheet_name='Sheet1')

workbook = writer.book
worksheet = writer.sheets['Sheet1']
worksheet.set_column('A:A',4)
worksheet.set_column('B:B',65)
worksheet.set_column('C:C',10)
worksheet.set_column('D:D',10)
worksheet.set_column('E:E',50)
worksheet.set_column('F:F',15)

worksheet.conditional_format('C2:C1001', {'type': '3_color_scale'})

writer.close()
