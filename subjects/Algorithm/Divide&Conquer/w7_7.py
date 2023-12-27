# Convex Hull Program in Python

import cv2
import numpy as np

points = []
all_points = []

def inclination(p1, p2):
    return p2[0] - p1[0], p2[1] - p1[1]
 
def ccw(p1, p2, p3):
    v, u = inclination(p1, p2), inclination(p2, p3)
    if v[0] * u[1] > v[1] * u[0]:
        return True
    return False
     
def convex_hull(positions):
    global points
    convex = list()
    for p3 in positions:
        while len(convex) >= 2:
            p1, p2 = convex[-2], convex[-1]
            if ccw(p1, p2, p3):
                break
            convex.pop()
        convex.append(p3)
    points.extend(convex)
 
def find_points(event, x, y, flags, param):
    global all_points
    if event == cv2.EVENT_LBUTTONUP:
        cv2.circle(img, (x,y), 2, (255,255,255), 4)
        all_points.append([x,y])

if __name__ == "__main__":

    image_dir = input('경로를 지정해주세요 (예시 _ C:/Users/MyFolder/Desktop/face.jpg) : ')
    dir = image_dir[:image_dir.find('.')]

    try:
        img = cv2.imread(image_dir)
        height, width = img.shape[:2]
        cv2.namedWindow('image')
        cv2.setMouseCallback('image',find_points)

    except:
        print('>>>>>>경로를 다시 지정하세요<<<<<<')
    while True:
        cv2.imshow('image', img)
        k = cv2.waitKey(1) & 0xFF 
        if k == 27 or k == ord(' '):              
            break

    all_points = sorted(all_points, key=lambda pos:(pos[0], pos[1]))
    convex_hull(all_points)
    points.pop()
    all_points.reverse()
    convex_hull(all_points)
    points.pop()

    pts = np.array(points, np.int32)
    pts = pts.reshape((-1, 1, 2))
    img = cv2.polylines(img, [pts], True, (255,255,255), 2)
    cv2.imshow('img', img)
    cv2.imwrite(dir+'_convexhull.jpg',img)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
