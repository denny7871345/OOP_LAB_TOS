import requests

def download_image(number):
    # 定義圖片的網址模板
    url_template = "https://madhead-dd03.myserver.asia/facebook/128/{}.png"
    
    # 使用輸入的數字替換模板中的佔位符
    url = url_template.format(number)
    
    # 發送HTTP GET請求來下載圖片
    response = requests.get(url)
    
    # 檢查請求是否成功
    if response.status_code == 200:
        # 定義圖片的儲存名稱
        file_name = f"{number}.png"
        
        # 將圖片內容寫入文件
        with open(file_name, 'wb') as file:
            file.write(response.content)
        
        print(f"圖片已成功下載並儲存為 {file_name}")
    else:
        print("下載失敗，請檢查網址或輸入的數字是否正確")

# 使用者輸入數字

if __name__ == "__main__":
    while(1):
        number = input("請輸入數字：")
        download_image(number)


