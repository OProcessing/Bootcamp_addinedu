
import cv2
import numpy as np
import math
from ultralytics import YOLO

model = YOLO('yolov8n-pose.pt')
img = cv2.imread('/home/han/Desktop/Han_ws/00.Data/08.YOLO/kirby.jpeg')
circle = cv2.imread('/home/han/Desktop/Han_ws/00.Data/06.openCV/data/circle.jpg')
circle = cv2.cvtColor(circle, cv2.COLOR_GRAY2BGR)
circle = cv2.resize(circle, (640, 480))
cap = cv2.VideoCapture("/dev/video0")

if not cap.isOpened() :
    raise RuntimeError("ERROR! Unable to open camera")

cvt_color = cv2.COLOR_BGR2GRAY
vflip = False
hflip = False
deg = 0
size = 0

try :
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    heigth = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    while True :
        ret, frame = cap.read()
        results = model(frame, stream=True)
        for r in results:
            keypoints = r.keypoints
            for ks in keypoints :
                k = np.array(ks.xy[0].cpu(), dtype=int)
                try:
                    xsize = abs(k[3][0] - k[4][0])
                    img2 = cv2.resize(img, (xsize + size, xsize + size))
                    img2H, img2W, img2C = img2.shape

                    x_offset = k[0][0] - int(img2W/2)
                    y_offset = k[0][1] - int(img2H/2)

                    roi = frame[y_offset:y_offset+img2H, x_offset:x_offset+img2W]
                    img2_gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
                    mask_inv = cv2.bitwise_not(img2_gray)
                    fg = cv2.bitwise_or(img2, img2, mask=mask_inv)
                    final_roi = cv2.add(roi, fg)
                    frame[y_offset:y_offset+img2H, x_offset:x_offset+img2W] = final_roi

                except Exception as e:
                    print(e)

        output = cv2.cvtColor(frame, cvt_color)
        output = cv2.add(output, circle)
        if vflip == True : output = cv2.flip(output, 0)
        if hflip == True : output = cv2.flip(output, 1)

        cp = (output.shape[1] / 2, output.shape[0] / 2)
        rot = cv2.getRotationMatrix2D(cp, deg, 1)
        output = cv2.warpAffine(output, rot, (0, 0))
        cv2.imshow('frame', output)


        input_key = cv2.waitKey(1)
        if input_key == 27 :
            break
        elif input_key & 0xFF == ord('k') : # flip
            img = cv2.imread('/home/han/Desktop/Han_ws/00.Data/08.YOLO/kirby.jpeg')
        elif input_key & 0xFF == ord('d') : # flip
            img = cv2.imread('/home/han/Desktop/Han_ws/00.Data/08.YOLO/doughnut.jpg')
        elif input_key & 0xFF == ord('p') : # flip
            size += 1
        elif input_key & 0xFF == ord('m') : # flip
            size -= 1
        elif input_key & 0xFF == ord('v') : # flip
            vflip = not vflip
        elif input_key & 0xFF == ord('h') : # flip
            hflip = not hflip
        elif input_key & 0xFF == ord('r') : # rotation
            deg += 1
        elif input_key & 0xFF == ord('g') : # gray
            cvt_color = cv2.COLOR_BGR2GRAY
        elif input_key & 0xFF == ord('c') : # color scale
            cvt_color = cv2.COLOR_BGR2BGRA


finally :
    cap.release()
    cv2.destroyAllWindows()
