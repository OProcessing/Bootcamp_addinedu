# [ADDINEDU](https://github.com/addinedu-ros-5th) ROS 개발 역량 강화를 위한 AI 자율주행 로봇 과정 5기
1. [01_EDA](#01_eda)
2. [02_SQL](#02_sql)
3. [03_Git](#03_git)
4. [04_Arduino](#04_arduino)
5. [05_PyQt](#05_pyqt)
6. [06_OpenCV](#06_opencv)
7. [07_Machine Learning](#07_machine-learning)

## 01_EDA

파이썬 기초와 라이브러리 numpy, pandas\
시각화 matplotlib, seaborn, folium, googlemaps\
크롤링 beautifulSoup, selenium

EDA oneday 프로젝트
* 빅뱅이론 정보 수집 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/01_EDA/src/0229_eda_bigbang_han.ipynb)
* 주유소 정보 수집 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/01_EDA/src/0229_eda_gasStation_han.ipynb)
* ~~주택청약 정보 수집 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/01_EDA/src/0229_eda_applyhome_han.ipynb)~~
```python
for season in tqdm(seasons):
    time.sleep(3)
    episode_list = imdb.find_elements(By.CLASS_NAME,season_class[2])    # episodes

    for episode in episode_list :
        
        title   = episode.find_element(By.CLASS_NAME,info_class[0]).text                    # head: season, episode, title
        content = episode.find_element(By.CLASS_NAME,info_class[1]).text                    # content
        date    = episode.find_element(By.CLASS_NAME,info_class[2]).text                    # aired date
        review  = episode.find_element(By.CLASS_NAME,info_class[3]).text.split(sep="\n")    # review : ratings, votes
        
        if re.search(head_pattern, title) :         # data seperate
            head = re.match(r"S(\d+).E(\d+)", title)
            head_season = head.group(1)
            head_episode = head.group(2)
            title = title.split(sep=" ", maxsplit=2)[2]
        else :                                      # exception
            head_season = 12
            head_episode = 25
        date = convert_us_date_to_korean(date)
        rating  = review[0]; vote = re.search(rate_pattern, review[2]).group(1)

        # merge
        episode_info = [head_season, head_episode, title, rating, vote, date, content]
        episode_info_list.append(episode_info)
    season_info_list.append(episode_info_list)
```

## 02_SQL
DB 구축과 SQL 기초\
SQL oneday 프로젝트
* 스타벅스와 이디야의 지점 비교 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/02_SQL/src/starbucks_edia_Han.ipynb)
```python
# 인접하지 않은 두 브랜드의 지점 위치
mapping = folium.Map(location=[37.53, 127], width="100%", height="100%", zoom_start=11.8)
namelist = distance[0].tolist()
for row in starbucks[0] :
    if row not in namelist :
        starbucks_far.append(row)

for idx, row in starbucks.iterrows():
    for name in starbucks_far :
        if row[0] == name :
            folium.CircleMarker( location=[row[1], row[2]], radius=10, fill=True, color='red', fill_color='red', tooltip=row[0]).add_to(mapping)
namelist = distance[1].tolist()
for row in ediya[0] :
    if row not in namelist :
        ediya_far.append(row)

for idx, row in ediya.iterrows():
    for name in ediya_far :
        if row[0] == name :
            folium.CircleMarker( location=[row[1], row[2]], radius=10, fill=True, color='red', fill_color='red', tooltip=row[0]).add_to(mapping)

```


## 03_Git
commit, log, version, branch

## 04_arduino
I/O, Timer, callback, register

## 05_PyQt
PyQt with arduino, MySQL

## 06_openCV
openCV, image processing, mask, overlay, projection

## 07_Machine Learning
머신러닝\
환경 설정 cuda, tensor flow\
라이브러리 sklearn\
데이터 전처리\
모델 학습 cost function, logistic regression, decision tree, kNN, ensemble, clustering, pipe line, MNIST\
Principal Component Analysis, eigen factor, image segment\

머신러닝 oneday 프로젝트
* 머신러닝 활용 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/07_MachineLearning/src/ox.ipynb)
딥러닝\
MNIST, CNN, VGG, Transfer learning\

딥러닝 oneday 프로젝트
* OX 이진구분 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/07_MachineLearning/src/0508_W12D3C1_OneDay.ipynb)
---
## 08_YOLO
Segment, Tracking, Pose Estimation

## ESP32
## ROS
## docker
