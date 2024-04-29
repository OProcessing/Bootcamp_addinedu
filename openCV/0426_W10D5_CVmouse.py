import cv2
import numpy as np

img = np.ones((512,512,3), np.uint8)

def draw_circle(event, x, y, flags, param) :
    if event == cv2.EVENT_LBUTTONDOWN :
        cv2.circle(img, (x,y), 30, (50,50,200), -1)

    if event == cv2.EVENT_RBUTTONDOWN :
        cv2.circle(img, (x,y), 30, (200,50,50), -1)
    
cv2.namedWindow(winname='cv_first_drawing')
cv2.setMouseCallback('cv_first_drawing', draw_circle, img)

while True:
    cv2.imshow('cv_first_drawing', img)
    if cv2.waitKey(10) == 27:
        break

cv2.destroyAllWindows()
