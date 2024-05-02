
import cv2

cap = cv2.VideoCapture("/dev/video0")

if not cap.isOpened() :
    raise RuntimeError("ERROR! Unable to open camera")

try :
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    heigth = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    print(f'width = {width}, heigth = {heigth}')
    
    fourcc = cv2.VideoWriter_fourcc(*'DIVX')
    out = cv2.VideoWriter('./text__.avi', fourcc, 20, (width, heigth), isColor=False)

    while True :
        ret, frame = cap.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow('frame', gray)
        out.write(gray)
        if cv2.waitKey(1) == 27 :
            break

finally :
    cap.release()
    out.release()
    cv2.destroyAllWindows()