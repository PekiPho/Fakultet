import numpy as np
import cv2 as cv
from collections import deque

detector = cv.SIFT_create()
MIN_MATCH_COUNT = 50


def spoji(img1, img2,count):
    kp1, des1 = detector.detectAndCompute(img1, None)
    kp2, des2 = detector.detectAndCompute(img2, None)

    #FLANN_INDEX_KDTREE = 1
    #index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    #search_params = dict(checks=50)
    #flann = cv.FlannBasedMatcher(index_params, search_params)

    bf = cv.BFMatcher(cv.NORM_L2, crossCheck=False)
    matches=bf.knnMatch(des1, des2,k=2)

    #matches = flann.knnMatch(des1, des2, k=2)

    good = []
    for m, n in matches:
        if m.distance < 0.7 * n.distance:
            good.append(m)

    if len(good) <= MIN_MATCH_COUNT:
        return None

    desne = list(filter(lambda el: kp1[el.queryIdx].pt[0] > img1.shape[1] // 2, good))
    vise_desnih = True if len(desne) > (len(good) // 2) else False
    leva_slika = img1 if vise_desnih else img2
    desna_slika = img2 if vise_desnih else img1

    pts1 = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
    pts2 = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)

    if vise_desnih:
        M, _ = cv.findHomography(pts2, pts1, cv.RANSAC, 5.0)
    else:
        M, _ = cv.findHomography(pts1, pts2, cv.RANSAC, 5.0)
    result = cv.warpPerspective(desna_slika, M, (desna_slika.shape[1] + leva_slika.shape[1], desna_slika.shape[0] + leva_slika.shape[0]))
    res_cpy = result.copy()

    #cv.imshow(f"Rezultat {count}", leva_slika)

    result[0:leva_slika.shape[0], 0:leva_slika.shape[1]] = leva_slika
    result = np.where(res_cpy == [0, 0, 0], result, res_cpy)
    ne_crni = np.where(result != [0, 0, 0])

    result = result[0:np.max(ne_crni[0]), 0:np.max(ne_crni[1])]
    return result


image1 = cv.imread('1.JPG')
image2 = cv.imread('2.jpg')
image3 = cv.imread('3.JPG')

stack = deque()
dq = deque()

curr_image = image1
stack.append(image2)
stack.append(image3)
count=0

while len(stack) > 0:

    second_image = stack.pop()
    merged = spoji(curr_image, second_image,count)
    if merged is not None:
        curr_image = merged
        while len(dq) > 0:
            stack.append(dq.pop())
    else:
        dq.append(second_image)
    count+=1

if curr_image is not None:
    cv.imshow("Rezultat", curr_image)
cv.waitKey(0)
