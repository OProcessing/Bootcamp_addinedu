# [ADDINEDU](https://github.com/addinedu-ros-5th) ROS 개발 역량 강화를 위한 AI 자율주행 로봇 과정 5기
## 목차
1. [EDA](#01_eda)
    - [EDA oneday 프로젝트](#eda-oneday-프로젝트)
2. [SQL](#02_sql)
    - [SQL oneday 프로젝트](#sql-oneday-프로젝트)
3. [EDA_Project](#eda_project)
4. [Git](#03_git)
5. [Arduino](#04_arduino)
6. [PyQt](#05_pyqt)
7. [IOT_Project](#iot_project)
8. [OpenCV](#06_opencv)
9. [Machine Learning](#07_machine-learning)
    - [머신러닝 oneday 프로젝트](#머신러닝-oneday-프로젝트)
    - [딥러닝 oneday 프로젝트](#딥러닝-oneday-프로젝트)
10. [You Only Look Once](#08_yolo)
11. [DeepLearning_Project](#deeplearning_project)
12. [ESP32](#esp32)
13. [ROS2](#ros2)
    - [ROS2 oneday 프로젝트](#ros2-oneday-프로젝트)
14. [docker](#docker)
15. [ROS2 프로젝트](#ros2-프로젝트)
## 01_EDA

파이썬 기초와 라이브러리 numpy, pandas\
시각화 matplotlib, seaborn, folium, googlemaps\
크롤링 beautifulSoup, selenium

### EDA oneday 프로젝트
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
&nbsp;

&nbsp;

&nbsp;
## 02_SQL
DB 구축과 SQL 기초

### SQL oneday 프로젝트
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

&nbsp;

&nbsp;

&nbsp;
## EDA_Project 
[[EDA 프로젝트]](https://github.com/addinedu-ros-5th/eda-repo-1)\
인기 롤 프레잉 게임인 리그 오브 레전드에서 유저들의 실력 향상을 위해 추천하는 방법에 대해\
개발사에서 제공하는 openAPI를 활용하여 정보를 수집하고 통계를 내어 실제로 효과가 있는지 검증한다.
```python
match_data = []
for matchIds in tqdm(matchId):
    for _matchId in matchIds:
        req = matchData(_matchId)
        if req.status_code == 200:
            data = req.json()
            match_data.append(data)
        else:
            print(req.status_code)
            break
        time.sleep(1.3)
len(match_data)
```

&nbsp;

&nbsp;

&nbsp;
## 03_Git
commit, log, version, branch

&nbsp;

&nbsp;

&nbsp;
## 04_arduino
I/O, Timer, callback, register

&nbsp;

&nbsp;

&nbsp;
## 05_PyQt
PyQt를 활용한 GUI에서 데이터베이스 호출, 쿼리 작성, 시각화와 아두이노 I/O 데이터 출력

&nbsp;

&nbsp;

&nbsp;
## IOT_Project
[[IOT 프로젝트]](https://github.com/addinedu-ros-5th/iot-repo-3/blob/main/README.md)\
물류센터에서의 입고부터 출고, 고객 배송까지의 과정을 시스템을 구현\
시스템 관리를 위한 GUI 제작, Log 기록을 통한 관리, 동작 구현과 유기적인 시스템 제작

&nbsp;

&nbsp;

&nbsp;
## 06_openCV
openCV, image processing, mask, overlay, projection

&nbsp;

&nbsp;

&nbsp;
## 07_Machine Learning
환경 설정 cuda, tensor flow\
라이브러리 sklearn\
데이터 전처리\
모델 학습 cost function, logistic regression, decision tree, kNN, ensemble, clustering, pipe line, MNIST\
Principal Component Analysis, eigen factor, image segment

### 머신러닝 oneday 프로젝트
* 머신러닝 활용 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/07_MachineLearning/src/0508_W12D3C1_OneDay.ipynb)
```python
# 11. 다시 원본 데이터에서 데이터를 test와 train으로 나눈 후, Standard scaler와 Decision Tree를 연달아 사용하는 pipeline을 꾸며 주세요.
x = iris_df
y = iris.target

estimators = [('scaler', StandardScaler()), ('clf', DecisionTreeClassifier(max_depth=2, random_state=50))]
pipe = Pipeline(estimators)

scores_rf = cross_validate(pipe, x, y, scoring='accuracy', cv=5)
scores_rf
```


  
딥러닝\
MNIST, CNN, VGG, Transfer learning

### 딥러닝 oneday 프로젝트
* OX 이진구분 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/07_MachineLearning/src/ox.ipynb)
```python
model = models.Sequential([
    layers.Conv2D(32, (3,3), activation='relu', input_shape=(128, 128, 3)),
    layers.MaxPooling2D(pool_size=(2, 2), strides=(2, 2)),
    layers.Dropout(0.24),

    layers.Conv2D(64, (3,3), activation='relu', padding='same'),
    layers.MaxPooling2D(pool_size=(2, 2)),
    layers.Dropout(0.25),

    layers.Conv2D(64, (3,3), activation='relu', padding='same'),
    layers.MaxPooling2D(pool_size=(2, 2)),
    layers.Dropout(0.25),

    layers.Flatten(),
    layers.Dense(512, activation='relu'),
    layers.Dropout(0.25),
    layers.Dense(2, activation='softmax')
])
model.summary()
```

&nbsp;

&nbsp;

&nbsp;
## 08_YOLO
Segment, Tracking, Pose Estimation

&nbsp;

&nbsp;

&nbsp;
## DeepLearning_Project
* ~~경로 추적 및 예측 [[URL]](https://github.com/OProcessing/Bootcamp_addinedu/blob/main/08_YOLO/src/PJ.ipynb)~~
```python
    detections = detect_objects(frame_rgb)
    dets = np.array([[x1, y1, x2, y2, conf] for x1, y1, x2, y2, conf in detections])
    tracked_objects = tracker.update(dets)

    for obj in tracked_objects:
        x1, y1, x2, y2, obj_id = obj[:5]
        center_x = (x1 + x2) / 2
        center_y = (y1 + y2) / 2
        current_pos = (center_x, center_y)

        prev_pos = previous_positions.get(obj_id, None)

        if prev_pos:
            speed, direction = calculate_speed_and_direction(prev_pos, current_pos, time_interval)
            cv2.putText(frame, f'ID: {int(obj_id)} Speed: {speed:.2f} Direction: {direction:.2f}',
                        (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)

        #draw_arrow_and_trajectory(frame, obj_id, center_x, center_y, prev_pos)

        previous_positions[obj_id] = current_pos
```
* 해산물 분류 및 가격정보 제공 솔루션 [[URL]](https://github.com/addinedu-ros-5th/deeplearning-repo-4)
&nbsp;
 
&nbsp;

&nbsp;
## ESP32
TCP 통신

&nbsp;

&nbsp;

&nbsp;
## ROS2
ROS2 node, topic, service, action, publisher, subscriber, pkg, openCV

### ROS2 oneday 프로젝트
* publisher [[URL]](https://github.com/OProcessing/ROS2_tutorial/blob/main/ROS_tutorial/src/my_first_package/my_first_package/oneday_set_flag.py)
* subscriber [[URL]](https://github.com/OProcessing/ROS2_tutorial/blob/main/ROS_tutorial/src/my_first_package/my_first_package/oneday_subscriber.py)
* 터틀심 tracking [[URL]](https://github.com/OProcessing/ROS2_tutorial/blob/main/ROS_tutorial/src/my_first_package/my_first_package/oneday_pen.py)

&nbsp;

&nbsp;

&nbsp;
## docker
docker 

&nbsp;

&nbsp;

&nbsp;
## ROS2 프로젝트
